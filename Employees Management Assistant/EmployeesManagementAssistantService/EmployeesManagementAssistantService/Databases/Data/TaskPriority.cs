namespace EmployeesManagementAssistantService.Databases.Data
{
    /// <summary> Данни за приоритет на задача </summary>
    public class TaskPriority : BaseData
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TaskPriority()
        {
            Name = "";
            Level = 0;
        }

        #endregion

        #region Properties

        /// <summary> Име на приоритета </summary>
        public string Name { get; set; }

        /// <summary> Ниво на приоритет </summary>
        public short Level { get; set; }

        #endregion
    }
}
