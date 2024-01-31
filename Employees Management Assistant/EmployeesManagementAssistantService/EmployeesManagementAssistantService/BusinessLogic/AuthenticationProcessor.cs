using EmployeesManagementAssistantService.Databases.Data;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace EmployeesManagementAssistantService.BusinessLogic
{
    /// <summary> Помощен клас за обработка на заявки за аутентикация </summary>
    public class AuthenticationProcessor
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public AuthenticationProcessor()
        {

        }

        #endregion

        #region Methods

        /// <summary> Връща токен </summary>
        public static string CreateToken(User user)
        {
            SecurityTokenDescriptor tokenDescriptor = new SecurityTokenDescriptor();
            tokenDescriptor.Expires = GetTokenTime();

            Claim[] claims = new Claim[]
            {
                new Claim(ClaimTypes.Role, user.ID.ToString())
            };

            ClaimsIdentity claimsIdentity = new ClaimsIdentity(claims);
            tokenDescriptor.Subject = claimsIdentity;

            SymmetricSecurityKey key = new SymmetricSecurityKey(GetTokenKey());
            SigningCredentials credentials = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);
            tokenDescriptor.SigningCredentials = credentials;

            JwtSecurityTokenHandler tokenHandler = new JwtSecurityTokenHandler();
            SecurityToken token = tokenHandler.CreateToken(tokenDescriptor);

            return tokenHandler.WriteToken(token);
        }

        /// <summary> Връща ключа на токена </summary>
        public static byte[] GetTokenKey() 
        {
            return Encoding.ASCII.GetBytes("k6q3T&(pGcXEhR)y");
        }

        /// <summary> Връща времето, за което токенът е валиден </summary>
        public static DateTime GetTokenTime()
        {
            return DateTime.Now.AddHours(12);
        }

        #endregion
    }
}
