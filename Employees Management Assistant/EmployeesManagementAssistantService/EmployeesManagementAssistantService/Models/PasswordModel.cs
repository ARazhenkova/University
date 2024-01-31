namespace EmployeesManagementAssistantService.Models
{
    /// <summary> Данни за парола </summary>
    public class PasswordModel
    {
        /// <summary> Идентификатор на потребителя </summary>
        public long UserID { get; set; }

        /// <summary> Текуща парола </summary>
        public string CurrentPassword { get; set; }

        /// <summary> Нова парола </summary>
        public string NewPassword { get; set; }
    }
}
