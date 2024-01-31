using System.Text;

namespace EmployeesManagementAssistantService.Databases.Data
{
    public class Task : BaseData
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public Task()
        {
            Name = "";
            PriorityID = 0;
            StateID = 0;
            AssignFromID = 0;
            AssignToID = 0;
            Description = "";
            ExternalPresentation = "";
        }

        #endregion

        #region Properties

        /// <summary> Име на задачата </summary>
        public string Name { get; set; }

        /// <summary> Индекс на приоритет </summary>
        public long PriorityID { get; set; }

        /// <summary> Индекс на статус </summary>
        public long StateID { get; set; }

        /// <summary> Индек на външния потребител, назначил задачата </summary>
        public long AssignFromID { get; set; }

        /// <summary> Индек на служител, на когото е назначена задачата </summary>
        public long AssignToID { get; set; }

        /// <summary> Описание </summary>
        public string Description { get; set; }

        /// <summary> Външно представяне </summary>
        public string ExternalPresentation { get; set; }

        #endregion

        #region Methods

        /// <summary> Създаване на външно представяне на задача </summary>
        public void CreateExternalPresentation()
        {
            Guid UID = Guid.NewGuid();
            string presentation = UID.ToString();
            byte[] bytes = Encoding.UTF8.GetBytes(presentation);
            ExternalPresentation = Convert.ToBase64String(bytes);
        }

        #endregion
    }
}
