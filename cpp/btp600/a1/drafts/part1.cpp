/**
 * Part 1 - Composite pattern (p. 163)
 */
#include <cstdlib>
class Graphic {
	public:
		virtual void Draw() const = 0;
		void Add(Graphic& graphicType) { }
		void Remove(Graphic& graphicType) { }
		Graphic* GetChild(int childNum) { return NULL; }
};

class Line : public Graphic {
	public:
		void Draw() { }
};

class Rectangle : public Graphic {
	public:
		void Draw() { }
};

class Text : public Graphic {
	public:
		void Draw() { }
};

class Picture : public Graphic {
	public:
		void Draw() { }
		void Add(Graphic& graphicType) { }
		void Remove(Graphic& graphicType) { }
		Graphic* GetChild(int childNum) {
			return NULL;
		}		
};