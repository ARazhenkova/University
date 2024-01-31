import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/internal/Observable';
import { AppAdditionalConfigurations } from '../app-additional-configurations';
import { User } from 'src/app/models/user.model';
import { UserPassword } from '../models/user.password.model';
import { JwtHelperService } from '@auth0/angular-jwt'

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {

  constructor(private http: HttpClient) { }

  isLoggedIn() {
    return this.getToken() != "" ? true : false;
  }

  login(user: User): Observable<User> {
    return this.http.post<User>(AppAdditionalConfigurations.baseURL + '/login', user)
  }

  public changePassword(UserPassword: UserPassword) {
    return this.http.put(AppAdditionalConfigurations.baseURL + '/change-password', UserPassword)
  }

  setToken(token: string): void {
    localStorage.setItem('token', token);
  }

  getToken(): string {
    const token = localStorage.getItem('token');

    if (token == null)
      return "";

    return token;
  }

  getUserID(): number {
    const token = this.getToken();

    const jwtHelper = new JwtHelperService();
    const data = jwtHelper.decodeToken(token);

    if (data == null)
      return 0;

    return data.role;
  }
}
