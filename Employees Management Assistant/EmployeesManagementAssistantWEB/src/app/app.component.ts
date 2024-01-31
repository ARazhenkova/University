import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AuthenticationService } from './services/authentication.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {

  constructor(public authenticationService: AuthenticationService, private router: Router) {}

  onLogout() {
    localStorage.clear();
    this.router.navigate([''])
  }
}
