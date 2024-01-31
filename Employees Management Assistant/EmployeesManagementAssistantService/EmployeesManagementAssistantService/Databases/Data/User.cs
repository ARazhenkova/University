using EmployeesManagementAssistantService.Models;

namespace EmployeesManagementAssistantService.Databases.Data
{
    public class User : BaseData
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public User()
        {
            Username = "";
            Password = "";
        }

        /// <summary> Kонструктор </summary>
        public User(UserModel userModel)
        {
            Username = userModel.Username;
            Password = userModel.Password;
        }

        #endregion

        #region Properties

        /// <summary> Потребителско име </summary>
        public string Username { get; set; }

        /// <summary> Парола </summary>
        public string Password { get; set; }

        /// <summary> Персонален ключ </summary>
        public string PersonalKey { get; set; }

        #endregion
    }
}
