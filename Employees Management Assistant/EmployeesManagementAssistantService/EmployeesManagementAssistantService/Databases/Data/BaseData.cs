
namespace EmployeesManagementAssistantService.Databases.Data
{
    public class BaseData
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public BaseData()
        {
            ID = 0;
            DataVersion = 0;
        }

        #endregion

        #region Properties

        /// <summary> Идентификатор </summary>
        public long ID { get; set; }

        /// <summary> Версия на данните в таблицата </summary>
        public long DataVersion { get; set; }

        #endregion

        #region Methods

        public void SetBaseData(BaseData data)
        {
            ID = data.ID;
            DataVersion = data.DataVersion;
        }

        #endregion
    }
}
