using EmployeesManagementAssistantService.Databases.BaseClasses;
using EmployeesManagementAssistantService.Databases.Data;
using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.Tables
{
    /// <summary> Колони в таблицата TASK_STATES </summary>
    public enum TaskStatesTableColumns
    {
        NAME = MandatoryTableColumns.Count,
        IS_FOR_ARCHIVE,
    }

    /// <summary> Клас за работа с таблица TASK_STATES </summary>
    public class TaskStatesTable : SqlTableManager<TaskState>
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TaskStatesTable() : base("TASK_STATES")
        {
        }

        /// <summary> Kонструктор </summary>
        public TaskStatesTable(TaskState taskState) : base("TASK_PRIORITIES", taskState)
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
            return "UPDATE_COUNTER";
        }

        /// <summary> Връща версията на данни от обект </summary>
        public override long GetDataVersion(TaskState taskState, bool increment)
        {
            if (increment)
                taskState.DataVersion++;

            return taskState.DataVersion;
        }

        /// <summary> Инициализация на колоните на таблицата </summary>
        protected override void SetColumns(List<SqlData> sqlColumns)
        {
            base.SetColumns(sqlColumns);
            sqlColumns.Add(new SqlData((long)TaskStatesTableColumns.NAME            , "NAME"            , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)TaskStatesTableColumns.IS_FOR_ARCHIVE  , "IS_FOR_ARCHIVE"  , SqlDataTypes.BOOLEAN));
        }

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected override void SetColumnsValue(TaskState taskState)
        {
            SetBaseColumnsValue(taskState);
            SetColumnValue((long)TaskStatesTableColumns.NAME            , taskState.Name);
            SetColumnValue((long)TaskStatesTableColumns.IS_FOR_ARCHIVE  , taskState.IsForArchive.ToString());
        }

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected override TaskState SetColumnsValue(SqlDataReader sqlDataReader)
        {
            TaskState taskState = new TaskState();

            taskState.SetBaseData(SetBaseColumnsValue(sqlDataReader));
            taskState.Name          = sqlDataReader.GetString((int)TaskStatesTableColumns.NAME);
            taskState.IsForArchive  = Convert.ToBoolean(sqlDataReader.GetByte((int)TaskStatesTableColumns.IS_FOR_ARCHIVE));

            return taskState;
        }

        #endregion
    }
}
