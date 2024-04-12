import { Component } from '@angular/core';
import { ApiService } from '../api.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css'],
})
export class RegisterComponent {
  username: any;
  email: any;
  password: any;
  constructor(private apiservice: ApiService) {}

  registerUser() {
    const newUser = {
      username: this.username,
      email: this.email,
      password: this.password,
    };

    this.apiservice.addUser(newUser).subscribe((response) => {
      console.log('New user added successfully', response);
    });
  }
}
