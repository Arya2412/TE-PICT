import { CanActivateFn } from '@angular/router';
import { Router } from '@angular/router';

export const authGuard: CanActivateFn = (route, state) => {
  if (!(localStorage.getItem('LoggedIn') === 'true')) {
    let router = new Router();
    router.navigate(['/register']);
    return false;
  }

  return true;
};
