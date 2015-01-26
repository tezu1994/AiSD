      Generyczna<ZrodlaDochodu*> selekcja(Generyczna<ZrodlaDochodu*> _generyczna) {
	ZrodlaDochodu *j, *d, *nowy;
      j = _generyczna.pobierzElement(0);
			d = stworzZrodlo();
			_generyczna+=d;
			wyswietlWszystkie(_generyczna);
			nowy = *j + d;
			_generyczna-=j;
			_generyczna-=d;
			_generyczna += nowy;
			cout << "Powstalo " << endl;
			cout << nowy->toString() << endl;
			j=nowy;
			
	return _generyczna;
}
