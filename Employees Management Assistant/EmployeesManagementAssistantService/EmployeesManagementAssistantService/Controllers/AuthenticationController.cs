using EmployeesManagementAssistantService.BusinessLogic;
using EmployeesManagementAssistantService.Databases.Data;
using EmployeesManagementAssistantService.Databases.Tables;
using EmployeesManagementAssistantService.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace EmployeesManagementAssistantService.Controllers
{
    [ApiController]
    [Route("external-tasks")]
    public class AuthenticationController : Controller
    {
        [HttpPost]
        [Route("login")]
        public IActionResult Login([FromBody] UserModel request)
        {
            UsersTable userTable = new UsersTable();
            User user = userTable.LoadUserByUsername(request.Username);

            // Потребителското име не съвпада
            if (user == null)
                return NotFound();

            // Паролата не съвпада
            Password password = new Password(request.Password, user.PersonalKey);
            if (user.Password != password.HashedPassword)
                return NotFound();

            // Създаване на токен
            string token = AuthenticationProcessor.CreateToken(user);

            UserModel response = new UserModel();
            response.Token = token;

            return Ok(response);
        }

        [Authorize]
        [HttpPut]
        [Route("change-password")]
        public IActionResult ChangePassword([FromBody] PasswordModel request)
        {
            UsersTable userTable = new UsersTable();
            User user = userTable.LoadRecordByID(request.UserID);

            if (user == null)
                return Problem();

            // Паролата не съвпада
            Password curredntPassword = new Password(request.CurrentPassword, user.PersonalKey);
            if (user.Password.Trim() != curredntPassword.HashedPassword)
                return Problem();

            // Записване на новата парола
            Password newPassword = new Password(request.NewPassword);
            user.Password = newPassword.HashedPassword;
            user.PersonalKey = newPassword.Salt;

            userTable.UpdateRecordByID(user);

            return Ok();
        }
    }
}
