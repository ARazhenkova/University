import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { User } from 'src/app/models/user.model';
import { AuthenticationService } from 'src/app/services/authentication.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit  {
  user = new User();
  isExistingUser: boolean = true;

  constructor(private authenticationService: AuthenticationService
            , private router: Router) {

  }
  
  ngOnInit(): void {

  }

  login(user: User): void {
    if(!this.isDataValid())
      return;

    this.authenticationService.login(user)
    .subscribe({
        next: (response: User) => {
        this.authenticationService.setToken(response.token)
        this.router.navigate(['tasks'])
      },
      error: (response: User) => {
        this.isExistingUser = false;
      }
    });
  }

  isDataValid(): boolean {
    if (this.user.username == "")
      return false;
    
    if (this.user.password == "")
      return false;

    return true;
  }
}
