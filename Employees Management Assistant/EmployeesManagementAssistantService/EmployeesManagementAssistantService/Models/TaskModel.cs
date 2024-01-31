namespace EmployeesManagementAssistantService.Models
{
    /// <summary> Данни за задача </summary>
    public class TaskModel
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TaskModel()
        {
            ID = 0;
            DataVersion = 0;
            UserID = 0;
            Name = "";
            Priority = "";
            State = "";
            Description = "";
            ExternalPresentation = "";
        }

        #endregion

        #region Properties

        /// <summary> Идентификатор </summary>
        public long ID { get; set; }

        /// <summary> Версия на данните в таблицата </summary>
        public long DataVersion { get; set; }

        /// <summary> Идентификатор на потребителя, назначил задачата </summary>
        public long UserID { get; set; }

        /// <summary> Име на задачата </summary>
        public string Name { get; set; }

        /// <summary> Индекс на приоритет </summary>
        public string Priority { get; set; }

        /// <summary> Индекс на статус </summary>
        public string State { get; set; }

        /// <summary> Описание </summary>
        public string Description { get; set; }

        /// <summary> Външно представяне </summary>
        public string ExternalPresentation { get; set; }

        #endregion
    }
}
