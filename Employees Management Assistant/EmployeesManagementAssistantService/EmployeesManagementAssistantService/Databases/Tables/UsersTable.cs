using EmployeesManagementAssistantService.Databases.BaseClasses;
using EmployeesManagementAssistantService.Databases.Data;
using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.Tables
{
    /// <summary> Колони в таблицата EXTERNAL_SYSTEM_USERS </summary>
    public enum UsersTableColumns
    {
        USERNAME = MandatoryTableColumns.Count,
        PASSWORD,
        PERSONAL_KEY,
    }

    /// <summary> Клас за работа с таблица EXTERNAL_SYSTEM_USERS </summary>
    public class UsersTable : SqlTableManager<User>
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public UsersTable() : base("EXTERNAL_SYSTEM_USERS")
        {

        }

        #endregion

        #region Overrides

        /// <summary> Връща името на ID колоната </summary>
        protected override string GetIDColumnName()
        {
            return "ID";
        }

        /// <summary> Връща името на DataVersion колоната </summary>
        protected override string GetDataVersionColumnName()
        {
            return "DATA_VERSION";
        }

        /// <summary> Връща версията на данни от обект </summary>
        public override long GetDataVersion(User user, bool increment)
        {
            if (increment)
                user.DataVersion++;

            return user.DataVersion;
        }

        /// <summary> Инициализация на колоните на таблицата </summary>
        protected override void SetColumns(List<SqlData> sqlColumns)
        {
            base.SetColumns(sqlColumns);
            sqlColumns.Add(new SqlData((long)UsersTableColumns.USERNAME         , "USERNAME"        , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)UsersTableColumns.PASSWORD         , "PASSWORD"        , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)UsersTableColumns.PERSONAL_KEY     , "PERSONAL_KEY"    , SqlDataTypes.STRING));
        }

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected override void SetColumnsValue(User user)
        {
            SetBaseColumnsValue(user);
            SetColumnValue((long)UsersTableColumns.USERNAME         , user.Username);
            SetColumnValue((long)UsersTableColumns.PASSWORD         , user.Password);
            SetColumnValue((long)UsersTableColumns.PERSONAL_KEY     , user.PersonalKey);
        }

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected override User SetColumnsValue(SqlDataReader sqlDataReader)
        {
            User user = new User();

            user.SetBaseData(SetBaseColumnsValue(sqlDataReader));
            user.Username       = sqlDataReader.GetString((int)UsersTableColumns.USERNAME);
            user.Password       = sqlDataReader.GetString((int)UsersTableColumns.PASSWORD);
            user.PersonalKey    = sqlDataReader.GetString((int)UsersTableColumns.PERSONAL_KEY);

            return user;
        }

        #endregion

        #region Methods

        /// <summary> Зареждане на потребител по потребителско име </summary>
        public User LoadUserByUsername(string username)
        {
            SetColumnValue((long)UsersTableColumns.USERNAME, username);
            string condition = GetColumnName((long)UsersTableColumns.USERNAME) + " = " + GetColumnValue((long)UsersTableColumns.USERNAME);
            return LoadRecord(condition);
        }

        #endregion
    }
}
