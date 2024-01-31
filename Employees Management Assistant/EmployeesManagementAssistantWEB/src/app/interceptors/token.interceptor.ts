import { Injectable } from '@angular/core';
import {
  HttpRequest,
  HttpHandler,
  HttpEvent,
  HttpInterceptor,
  HttpErrorResponse
} from '@angular/common/http';
import { catchError, Observable, throwError } from 'rxjs';
import { Router } from '@angular/router';
import { AuthenticationService } from '../services/authentication.service';

@Injectable()
export class TokenInterceptor implements HttpInterceptor {

  constructor(private router: Router
            , private authenticationService: AuthenticationService) {

  }

  intercept(request: HttpRequest<unknown>, next: HttpHandler): Observable<HttpEvent<unknown>> {
    const token = this.authenticationService.getToken();

    if (token != "") {
      request = request.clone({
        setHeaders: {Authorization: `Bearer ${token}`}
      })
    }

    return next.handle(request).pipe(
      catchError((error: any) => {
        if (error instanceof HttpErrorResponse) {
          if (error.status === 401) {
            localStorage.clear();
            this.router.navigate(['']);
          }
        }

        return throwError(() => new Error());
      })
    );
  }
}
