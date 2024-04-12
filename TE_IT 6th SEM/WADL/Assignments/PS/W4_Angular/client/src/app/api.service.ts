import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root',
})
export class ApiService {
  constructor(private http: HttpClient) {}

  baseUrl: any = 'http://localhost:3000/users';

  getUsers() {
    return this.http.get(this.baseUrl);
  }

  addUser(user: any) {
    return this.http.post(this.baseUrl, user);
  }
}
