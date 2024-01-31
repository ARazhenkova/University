using EmployeesManagementAssistantService.Databases.Data;
using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.BaseClasses
{
    /// <summary> Основни задължителни колони във всяка таблица </summary>
    public enum MandatoryTableColumns
    {
        ID = 0,
        DATA_VERSION,
        Count,
    }

    /// <summary> Базов клас за работа с таблицата </summary>
    public abstract class SqlTableManager<DataType> : SqlManager<DataType> where DataType : class
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public SqlTableManager(string tableName) : base(tableName)
        {
            SqlColumns = new List<SqlData>();
            SetColumns(SqlColumns);
        }

        /// <summary> Kонструктор </summary>
        public SqlTableManager(string tableName, DataType data) : base(tableName)
        {
            SqlColumns = new List<SqlData>();
            SetColumns(SqlColumns);
            SetColumnsValue(data);
        }

        #endregion

        #region Abstract

        /// <summary> Връща името на ID колоната </summary>
        protected abstract string GetIDColumnName();

        /// <summary> Връща името на DataVersion колоната </summary>
        protected abstract string GetDataVersionColumnName();

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected abstract void SetColumnsValue(DataType data);

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected abstract DataType SetColumnsValue(SqlDataReader sqlDataReader);

        #endregion

        #region Overrides

        /// <summary> Обработка на данните, изчетени от таблицата </summary>
        protected override DataType ProccessSqlReaderData(SqlDataReader sqlDataReader)
        {
            return SetColumnsValue(sqlDataReader);
        }

        #endregion

        #region Properties

        /// <summary> Колони на таблицата </summary>
        private List<SqlData> SqlColumns { get; set; }

        #endregion

        #region Methods

        /// <summary> Зареждане на записи </summary>
        public virtual List<DataType> LoadRecords(IsolationLevels isolationLevel = IsolationLevels.NOLOCK, string condition = "")
        {
            return LoadRecords(GetAllColumnsData(ReturnColumnDataTypes.Name, false), isolationLevel, condition);
        }

        /// <summary> Зареждане на запис </summary>
        public virtual DataType LoadRecord(string condition, IsolationLevels isolationLevel = IsolationLevels.NOLOCK)
        {
            DataType data = null;

            List<DataType> dataList = LoadRecords(GetAllColumnsData(ReturnColumnDataTypes.Name, false), isolationLevel, condition);

            if (dataList.Count > 0)
                data = dataList[0];

            return data;
        }

        /// <summary> Зареждане на запис по идентификатор </summary>
        public virtual DataType LoadRecordByID(long ID, IsolationLevels isolationLevel = IsolationLevels.NOLOCK)
        {
            string condition = GetColumnName((long)MandatoryTableColumns.ID) + " = " + ID;

            return LoadRecord(condition);
        }

        /// <summary> Добавяне на запис </summary>
        public virtual void InsertRecord(DataType data)
        {
            SetColumnsValue(data);

            InsertRecord(GetAllColumnsData(ReturnColumnDataTypes.Name, true)
                       , GetAllColumnsData(ReturnColumnDataTypes.Value, true));
        }

        /// <summary> Редакция на запис </summary>
        public virtual void UpdateRecord(DataType data, string condition = "")
        {
            SetColumnsValue(data);

            UpdateRecord(GetAllColumnsData(ReturnColumnDataTypes.Name, true)
                       , GetAllColumnsData(ReturnColumnDataTypes.NameAndValue, true)
                       , data
                       , condition);
        }

        /// <summary> Редакция на запис по идентификатор </summary>
        public void UpdateRecordByID(DataType data)
        {
            GetDataVersion(data, true);
            SetColumnsValue(data);

            string condition = GetColumnName((long)MandatoryTableColumns.ID) + " = " + GetColumnValue((long)MandatoryTableColumns.ID);

            UpdateRecord(GetAllColumnsData(ReturnColumnDataTypes.Name, false)
                       , GetAllColumnsData(ReturnColumnDataTypes.NameAndValue, true)
                       , data
                       , condition);
        }

        /// <summary> Изтриване на запис </summary>
        public virtual void DeleteRecord(DataType data, string condition = "")
        {
            SetColumnsValue(data);
            DeleteRecord(condition);
        }

        /// <summary> Изтриване на запис по идентификатор </summary>
        public void DeleteRecordByID(long ID)
        {
            string condition = GetColumnName((long)MandatoryTableColumns.ID) + " = " + ID;

            DeleteRecord(condition);
        }

        /// <summary> Връща данни за предварително инициализирана колона </summary>
        protected SqlData GetColumn(long index)
        {
            return SqlColumns.Find(field => field.Index == index);
        }

        /// <summary> Връща името на предварително инициализирана колона </summary>
        protected string GetColumnName(long index)
        {
            SqlData sqlData = GetColumn(index);
            return "[" + sqlData.Name + "]";
        }

        /// <summary> Връща стойността на предварително инициализирана колона </summary>
        protected string GetColumnValue(long index)
        {
            SqlData sqlData = GetColumn(index);
            return GetColumnValue(sqlData);
        }

        /// <summary> Връща стойността на предварително инициализирана колона </summary>
        protected string GetColumnValue(SqlData sqlData)
        {
            string value = "";

            switch (sqlData.SqlDataType)
            {
                case SqlDataTypes.STRING:
                case SqlDataTypes.DATETIME:
                    value = "N'" + sqlData.Value + "'";
                    break;
                default:
                    value = sqlData.Value;
                    break;
            }

            return value;
        }

        /// <summary> Задава стойност на предварително инициализирана колона </summary>
        protected void SetColumnValue(long index, string value)
        {
            SqlData sqlData = GetColumn(index);
            sqlData.Value = value;
        }

        /// <summary> Какъв тип данни да се връща  </summary>
        protected enum ReturnColumnDataTypes
        {
            Name = 0,
            Value,
            NameAndValue,
        }

        /// <summary> Връща данни за всички колони </summary>
        protected string GetAllColumnsData(ReturnColumnDataTypes columnData, bool skipID)
        {
            string columnsValues = "";
            long lastIndex = SqlColumns.Count() - 1;

            for (int index = 0; index < SqlColumns.Count(); index++)
            {
                SqlData sqlColumn = SqlColumns[index];

                if (skipID && sqlColumn.Index == (long)MandatoryTableColumns.ID)
                    continue;

                switch (columnData)
                {
                    case ReturnColumnDataTypes.Name:
                        columnsValues += "[" + sqlColumn.Name + "]";
                        break;
                    case ReturnColumnDataTypes.Value:
                        columnsValues += GetColumnValue(sqlColumn);
                        break;
                    case ReturnColumnDataTypes.NameAndValue:
                        columnsValues += "[" + sqlColumn.Name + "] = " + GetColumnValue(sqlColumn);
                        break;
                }

                if (index != lastIndex)
                    columnsValues += ", ";
            }

            return columnsValues;
        }

        /// <summary> Инициализация на колоните на таблицата </summary>
        protected virtual void SetColumns(List<SqlData> sqlColumns)
        {
            sqlColumns.Add(new SqlData((long)MandatoryTableColumns.ID            , GetIDColumnName()            , SqlDataTypes.INT));
            sqlColumns.Add(new SqlData((long)MandatoryTableColumns.DATA_VERSION  , GetDataVersionColumnName()   , SqlDataTypes.INT));
        }

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected virtual void SetBaseColumnsValue(BaseData data)
        {
            SetColumnValue((long)MandatoryTableColumns.ID            , data.ID.ToString());
            SetColumnValue((long)MandatoryTableColumns.DATA_VERSION  , data.DataVersion.ToString());
        }

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected virtual BaseData SetBaseColumnsValue(SqlDataReader sqlDataReader)
        {
            BaseData data = new BaseData();

            data.ID             = sqlDataReader.GetInt32((int)MandatoryTableColumns.ID);
            data.DataVersion    = sqlDataReader.GetInt32((int)MandatoryTableColumns.DATA_VERSION);

            return data;
        }

        #endregion
    }
}
