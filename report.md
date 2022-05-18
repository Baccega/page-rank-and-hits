Ho scelto di usare `pair<double, int>` invece della piú intuitiva `pair<int, double>` perché di default il confronto tra pairs utilizza il primo valore, quindi nel mio caso mettendo prima il double (lo score) posso fare i confronti necessari per l'heap nella maniera piú semplice possibile.



