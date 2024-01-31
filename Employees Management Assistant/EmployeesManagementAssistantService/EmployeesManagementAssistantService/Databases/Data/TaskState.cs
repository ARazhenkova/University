namespace EmployeesManagementAssistantService.Databases.Data
{
    /// <summary> Данни за състояние на задача </summary>
    public class TaskState : BaseData
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TaskState()
        {
            Name = "";
            IsForArchive = false;
        }

        #endregion

        #region Properties

        /// <summary> Име на приоритета </summary>
        public string Name { get; set; }

        /// <summary> Дали задачата е приключена и за архивиране </summary>
        public bool IsForArchive { get; set; }

        #endregion
    }
}
