using EmployeesManagementAssistantService.Databases.BaseClasses;
using EmployeesManagementAssistantService.Databases.Data;
using System.Data.SqlClient;

namespace EmployeesManagementAssistantService.Databases.Tables
{
    /// <summary> Колони в таблицата TASK_PRIORITIES </summary>
    public enum TaskPrioritiesTableColumns
    {
        NAME = MandatoryTableColumns.Count,
        LEVEL,
    }

    /// <summary> Клас за работа с таблица TASK_PRIORITIES </summary>
    public class TaskPrioritiesTable : SqlTableManager<TaskPriority>
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TaskPrioritiesTable() : base("TASK_PRIORITIES")
        {
        }

        /// <summary> Kонструктор </summary>
        public TaskPrioritiesTable(TaskPriority taskPriority) : base("TASK_PRIORITIES", taskPriority)
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
        public override long GetDataVersion(TaskPriority taskPriority, bool increment)
        {
            if (increment)
                taskPriority.DataVersion++;

            return taskPriority.DataVersion;
        }

        /// <summary> Инициализация на колоните на таблицата </summary>
        protected override void SetColumns(List<SqlData> sqlColumns)
        {
            base.SetColumns(sqlColumns);
            sqlColumns.Add(new SqlData((long)TaskPrioritiesTableColumns.NAME    , "NAME"    , SqlDataTypes.STRING));
            sqlColumns.Add(new SqlData((long)TaskPrioritiesTableColumns.LEVEL   , "LEVEL"   , SqlDataTypes.INT));
        }

        /// <summary> Попълване на стойности от обект в колоните на таблицата </summary>
        protected override void SetColumnsValue(TaskPriority taskPriority)
        {
            SetBaseColumnsValue(taskPriority);
            SetColumnValue((long)TaskPrioritiesTableColumns.NAME    , taskPriority.Name);
            SetColumnValue((long)TaskPrioritiesTableColumns.LEVEL   , taskPriority.Level.ToString());
        }

        /// <summary> Попълване на стойности от колоните на таблицата в обект </summary>
        protected override TaskPriority SetColumnsValue(SqlDataReader sqlDataReader)
        {
            TaskPriority taskPriority = new TaskPriority();

            taskPriority.SetBaseData(SetBaseColumnsValue(sqlDataReader));
            taskPriority.Name   = sqlDataReader.GetString((int)TaskPrioritiesTableColumns.NAME);
            taskPriority.Level  = sqlDataReader.GetInt16((int)TaskPrioritiesTableColumns.LEVEL);

            return taskPriority;
        }

        #endregion
    }
}
