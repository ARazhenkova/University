namespace EmployeesManagementAssistantService.Models
{
    /// <summary> Входни данни на заявката за аутентикация </summary>
    public class UserModel
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public UserModel()
        {
            Username = "";
            Password = "";
            Token = "";
        }

        #endregion

        #region Properties

        public long ID { get; set; }

        /// <summary> Потребителско име </summary>
        public string Username { get; set; }

        /// <summary> Парола </summary>
        public string Password { get; set; }

        /// <summary> Токен</summary>
        public string Token { get; set; }

        #endregion
    }
}
