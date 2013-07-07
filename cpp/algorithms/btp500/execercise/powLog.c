/* pow with a run time of O (log n) */

int pow (a, b) {
	int r;
	if (a == 0)
		r = 1;
	else {
		r = pow(a, b / 2);
		if (b%2)
			r = a * r * r;
		else
			r = r * r;
	}
	return r;
}
	