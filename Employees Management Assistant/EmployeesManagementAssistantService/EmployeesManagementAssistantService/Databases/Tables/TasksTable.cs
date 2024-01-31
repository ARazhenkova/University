using EmployeesManagementAssistantService.Databases.BaseClasses;
using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.Tables
{
    /// <summary> Колони в таблицата EXTERNAL_SYSTEM_TASKS </summary>
    public enum TasksTableColumns
    {
        NAME = MandatoryTableColumns.Count,
        PRIORITY_ID,
        STATE_ID,
        ASSIGN_FROM_ID,
        ASSIGN_TO_ID,
        DESCRIPTION,
        EXTERNAL_PRESENTATION,
    }

    /// <summary> Клас за работа с таблица EXTERNAL_SYSTEM_TASKS </summary>
    public class TasksTable : SqlTableManager<Data.Task>
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TasksTable() : base("EXTERNAL_SYSTEM_TASKS")
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
        public override long GetDataVersion(Data.Task task, bool increment)
        {
            if (increment)
                task.DataVersion++;

            return task.DataVersion;
        }

        /// <summary> Инициализация на колоните на таблицата </summary>
        protected override void SetColumns(List<SqlData> sqlColumns)
        {
            base.SetColumns(sqlColumns);
            sqlColumns.Add(new SqlData((long)TasksTableColumns.NAME                     , "NAME"                    , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.PRIORITY_ID              , "PRIORITY_ID"             , SqlDataTypes.INT));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.STATE_ID                 , "STATE_ID"                , SqlDataTypes.INT));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.ASSIGN_FROM_ID           , "ASSIGN_FROM_ID"          , SqlDataTypes.INT));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.ASSIGN_TO_ID             , "ASSIGN_TO_ID"            , SqlDataTypes.INT));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.DESCRIPTION              , "DESCRIPTION"             , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)TasksTableColumns.EXTERNAL_PRESENTATION    , "EXTERNAL_PRESENTATION"   , SqlDataTypes.STRING));
        }

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected override void SetColumnsValue(Data.Task task)
        {
            SetBaseColumnsValue(task);
            SetColumnValue((long)TasksTableColumns.NAME                     , task.Name);
            SetColumnValue((long)TasksTableColumns.PRIORITY_ID              , task.PriorityID.ToString());
            SetColumnValue((long)TasksTableColumns.STATE_ID                 , task.StateID.ToString());
            SetColumnValue((long)TasksTableColumns.ASSIGN_FROM_ID           , task.AssignFromID.ToString());
            SetColumnValue((long)TasksTableColumns.ASSIGN_TO_ID             , task.AssignToID.ToString());
            SetColumnValue((long)TasksTableColumns.DESCRIPTION              , task.Description.ToString());
            SetColumnValue((long)TasksTableColumns.EXTERNAL_PRESENTATION    , task.ExternalPresentation.ToString());
        }

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected override Data.Task SetColumnsValue(SqlDataReader sqlDataReader)
        {
            Data.Task task = new Data.Task();

            task.SetBaseData(SetBaseColumnsValue(sqlDataReader));
            task.Name                   = sqlDataReader.GetString((int)TasksTableColumns.NAME);
            task.PriorityID             = sqlDataReader.GetInt32((int)TasksTableColumns.PRIORITY_ID);
            task.StateID                = sqlDataReader.GetInt32((int)TasksTableColumns.STATE_ID);
            task.AssignFromID           = sqlDataReader.GetInt32((int)TasksTableColumns.ASSIGN_FROM_ID);
            task.AssignToID             = sqlDataReader.GetInt32((int)TasksTableColumns.ASSIGN_TO_ID);
            task.Description            = sqlDataReader.GetString((int)TasksTableColumns.DESCRIPTION);
            task.ExternalPresentation   = sqlDataReader.GetString((int)TasksTableColumns.EXTERNAL_PRESENTATION);

            return task;
        }

        #endregion

        #region Methods

        /// <summary> Зареждане на всички задачи, въведени от определен външен потребител </summary>
        public List<Data.Task> LoadRecordsByExternalUserID(long ExternalUserID)
        {
            string condition = GetColumnName((long)TasksTableColumns.ASSIGN_FROM_ID) + " = " + ExternalUserID;
            List<Data.Task> tasks = LoadRecords(IsolationLevels.NOLOCK, condition);
            return tasks;
        }

        #endregion
    }
}
