import { ChangeDetectorRef, Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { UserPassword } from 'src/app/models/user.password.model';
import { AuthenticationService } from 'src/app/services/authentication.service';

@Component({
  selector: 'app-change-password',
  templateUrl: './change-password.component.html',
  styleUrls: ['./change-password.component.css']
})
export class ChangePasswordComponent implements OnInit {
  userPassword: UserPassword = new UserPassword();
  confirmPassword: string = "";

  isPasswordConfirmed: boolean = true;
  isPasswordValid: boolean = true;

  constructor(private authenticationService: AuthenticationService
            , private router: Router
            , private changeDetectorRef: ChangeDetectorRef) {

  }

  ngOnInit(): void {

  }

  ngAfterViewChecked(): void {
    this.changeDetectorRef.detectChanges(); // за опресняване на съобщенията
  }

  changePassword(): void {
    if(!this.isDataValid())
      return;

    this.userPassword.userID = this.authenticationService.getUserID();

    this.authenticationService.changePassword(this.userPassword)
    .subscribe({
      next: (response) => {       
        localStorage.clear();
        this.router.navigate([''])
      },
      error: (response) => {
        this.isPasswordValid = false;
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['tasks'])
  }

  isDataValid(): boolean {
    if(this.userPassword.currentPassword == "")
      return false;

    if(this.userPassword.newPassword == "")
      return false;

    if(this.userPassword.newPassword != this.confirmPassword) {
      this.isPasswordConfirmed = false;
      this.isPasswordValid = true; // за да може да излиза само едно съобщение
      return false;
    }

    this.isPasswordConfirmed = true;

    return true;
  }
}
