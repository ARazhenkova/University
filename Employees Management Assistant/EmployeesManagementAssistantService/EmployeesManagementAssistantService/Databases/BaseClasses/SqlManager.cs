using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.BaseClasses
{
    public enum IsolationLevels
    {
        NOLOCK = 0,
        UPDLOCK,
    }

    /// <summary> Базов клас за работа с MSSQL </summary>
    public abstract class SqlManager<DataType> where DataType : class
    {
        #region Members

        private string _connectionString = @"Server=ARAZ-DESKTOP\SQL2019;Database=EMPLOYEES_MANAGEMENT_ASSISTANT;User Id=employee;Password=12345;";

        /// <summary> Име на таблицата </summary>
        private string _tableName;

        #endregion

        #region Constructor

        /// <summary> Kонструктор </summary>
        public SqlManager(string TableName)
        {
            _tableName = TableName;
        }

        #endregion

        #region Abstract

        /// <summary> Връща версията на данни от обект </summary>
        public abstract long GetDataVersion(DataType data, bool increment);

        /// <summary> Обработка на данните, изчетени от таблицата </summary>
        protected abstract DataType ProccessSqlReaderData(SqlDataReader sqlDataReader);

        #endregion

        #region Methods

        /// <summary> Връща името на таблицата </summary>
        public string GetTableName() { return "[" + _tableName + "]"; }

        /// <summary> Зареждане на записи </summary>
        protected List<DataType> LoadRecords(string columns, IsolationLevels isolationLevel = IsolationLevels.NOLOCK, string condition = "")
        {
            string query = "SELECT " + columns + " FROM " + GetTableName() + GetIsolationLevel(isolationLevel);

            if (!string.IsNullOrEmpty(condition))
                query += " WHERE " + condition;

            return ExecuteReadQuery(query);
        }

        /// <summary> Добавяне на запис </summary>
        protected void InsertRecord(string columns, string values)
        {
            string query = "INSERT INTO " + GetTableName() + " (" + columns + ") VALUES(" + values + ")";
            ExecuteQuery(query);
        }

        /// <summary> Редакция на запис </summary>
        protected DataType UpdateRecord(string columns, string updateData, DataType newData, string condition = "")
        {
            string readQuery = "SELECT " + columns + " FROM " + GetTableName() + GetIsolationLevel(IsolationLevels.UPDLOCK);
            string updateQuery = "UPDATE " + GetTableName() + " SET " + updateData;

            // Каквото редактираме, трябва първо да се изчете със заключване
            if (!string.IsNullOrEmpty(condition))
            {
                readQuery += " WHERE " + condition;
                updateQuery += " WHERE " + condition;
            }
                
            return ExecuteUpdateQuery(newData, readQuery, updateQuery);
        }

        /// <summary> Изтриване на запис </summary>
        public virtual void DeleteRecord(string condition = "")
        {
            string query = "DELETE " + GetTableName();

            if (!string.IsNullOrEmpty(condition))
                query += " WHERE " + condition;

            ExecuteQuery(query);
        }

        private string GetIsolationLevel(IsolationLevels isolationLevel)
        {
            switch (isolationLevel)
            {
                case IsolationLevels.NOLOCK:
                    return " WITH(NOLOCK)";
                case IsolationLevels.UPDLOCK:
                    return " WITH(UPDLOCK)";
                default:
                    return "";
            }
        }

        #endregion

        #region SQLQueryExecutions

        /// <summary> Изчитане на записи </summary>
        public virtual List<DataType> ExecuteReadQuery(string query)
        {
            List<DataType> dataList = new List<DataType>();

            using (SqlConnection sqlConnection = new SqlConnection(_connectionString))
            {
                sqlConnection.Open();

                SqlCommand sqlCommand = new SqlCommand(query, sqlConnection);
                SqlDataReader sqlDataReader = sqlCommand.ExecuteReader();

                while (sqlDataReader.Read())
                {
                    DataType data = ProccessSqlReaderData(sqlDataReader);
                    dataList.Add(data);
                }

                sqlDataReader.Close(); 
            }

            return dataList;
        }

        /// <summary> Изчитане на записи </summary>
        public DataType ExecuteUpdateQuery(DataType newData, string readQuery, string updateQuery)
        {
            try
            {
                using (SqlConnection sqlConnection = new SqlConnection(_connectionString))
                {
                    sqlConnection.Open();

                    // Зареждане на текущите данни
                    SqlCommand sqlReadCommand = new SqlCommand(readQuery, sqlConnection);
                    SqlDataReader sqlDataReader = sqlReadCommand.ExecuteReader();

                    if (!sqlDataReader.HasRows)
                        throw new ArgumentException("Table is emplty.");

                    if (!sqlDataReader.Read())
                        throw new ArgumentException("Failed to read the record.");

                    DataType currentData = ProccessSqlReaderData(sqlDataReader);

                    // Проверка дали версията на изчетените данни съвпада с тази на данните, които искаме да запишем 
                    if (GetDataVersion(currentData, false) != GetDataVersion(newData, false) - 1)
                        throw new ArgumentException("Invalid data version.");

                    sqlDataReader.Close();

                    // Редактиране на данните
                    SqlCommand sqlUpdateCommand = new SqlCommand(updateQuery, sqlConnection);
                    sqlUpdateCommand.ExecuteNonQuery();
                }
            }
            catch(Exception ex)
            {

            }

            return newData;
        }

        /// <summary> Изпълняване на заявка към базата </summary>
        public virtual void ExecuteQuery(string query)
        {
            using (SqlConnection sqlConnection = new SqlConnection(_connectionString))
            {
                sqlConnection.Open();

                SqlCommand sqlCommand = new SqlCommand(query, sqlConnection);
                sqlCommand.ExecuteNonQuery();
            }
        }

        #endregion
    }
}
