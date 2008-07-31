void
bstack(void) {
	int x, y, h, w, mh;
	uint i, n;
	Client *c;

	for(n = 0, c = nexttiled(clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;

	/* master */
	c = nexttiled(clients);
	mh = mfact * wh;
	resize(c, wx, wy, ww - 2 * c->bw, (n == 1 ? wh : mh) - 2 * c->bw, resizehints);

	if(--n == 0)
		return;

	/* tile stack */
	x = wx;
	y = (wy + mh > c->y + c->h) ? c->y + c->h + 2 * c->bw : wy - mh;
	w = ww / n;
	h = (wy + mh > c->y + c->h) ? wy + wh - y : wh - mh;
	if(h < bh)
		h = wh;

	for(i = 0, c = nexttiled(c->next); c; c = nexttiled(c->next), i++) {
		resize(c, x, y, /* remainder */ ((i + 1 == n) ? (wx + ww) - x
		       : w) - 2 * c->bw, h - 2 * c->bw, resizehints);
		if(w != ww)
			x = c->x + c->w + 2 * c->bw;	
	}
}
