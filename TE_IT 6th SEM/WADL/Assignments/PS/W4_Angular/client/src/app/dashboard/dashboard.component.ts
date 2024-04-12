import { Component } from '@angular/core';
import { ApiService } from '../api.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css'],
})
export class DashboardComponent {
  details: any;
  constructor(private apiservice: ApiService, private router: Router) {}
  ngOnInit(): void {
    this.details = {
      username: localStorage.getItem('username'),
      email: localStorage.getItem('email'),
    };
  }

  logout() {
    localStorage.clear();
    this.router.navigate(['/register']);
  }
}
