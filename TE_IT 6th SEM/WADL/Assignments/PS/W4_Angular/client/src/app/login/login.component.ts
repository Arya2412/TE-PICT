import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService } from '../api.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
})
export class LoginComponent {
  username: any;
  email: any;
  password: any;
  users: any = [];

  constructor(private apiservice: ApiService, private router: Router) {}

  ngOnInit(): void {
    this.apiservice.getUsers().subscribe((res) => (this.users = res));
  }

  loginUser() {
    const data = {
      username: this.username,
      email: this.email,
      password: this.password,
    };

    if (data.username) {
      let flag = 0;
      this.users.forEach((item: any) => {
        if (
          item.username === data.username &&
          item.email === data.email &&
          item.password == data.password
        ) {
          localStorage.setItem('LoggedIn', 'true');
          localStorage.setItem('username', item.username);
          localStorage.setItem('email', item.email);
          flag = 1;
          this.router.navigate(['/dashboard']);
        }
      });

      if (flag == 0) {
        alert('Invalid');
      }
    }
  }
}
