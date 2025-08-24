In riferimento ad un oggetto troveremo quindi:

• lo state (it: stato), ovvero quali sono le caratteristiche interne che lo vanno a definire e
con il
• behavior (it: comportamento) ovvero cosa possiamo fare con esso.


```java
public interface Light {

void on () ;

void off () ;

}
```
Ci da solo informazioni sulle funzioni che avra' la lampadina.
```java
public class MyLight implements Light {
	private boolean isOn = false ;
	
	public void on () {
		isOn = true ;
	}
	
	public void off () {
		isOn = false ;
	}
	public boolean isOn () {
		return isOn ;
	}
}
```
Spiega costruttore, default constructor, new, campi e metodi (campi+metodi sono i membri)
Static

---
Information hiding
Inheritance
Polymorphism 