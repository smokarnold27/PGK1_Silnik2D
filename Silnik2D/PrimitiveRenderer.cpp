#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

PrimitiveRenderer::PrimitiveRenderer() {
	bufferWidth = GetScreenWidth();
	bufferHeight = GetScreenHeight();

	pixels.resize(bufferWidth * bufferHeight, WHITE);
}
PrimitiveRenderer ::~PrimitiveRenderer() {}

void PrimitiveRenderer::PutPixel(const Point2D& point, Color color) const {
	PutPixel(point.GetX(), point.GetY(), color);
}

void PrimitiveRenderer::PutPixel(int x, int y, Color color) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return;

	pixels[y * bufferWidth + x] = color;
}

void PrimitiveRenderer::DrawLine(const Point2D& p1, const Point2D& p2, Color color) const
{
    int x0 = p1.GetX();
    int y0 = p1.GetY();
    int x1 = p2.GetX();
    int y1 = p2.GetY();

    int dx = x1 - x0;
    int dy = y1 - y0;

	if (abs(dy) <= abs(dx)) { // Linia jest bardziej pozioma niż pionowa (|m| <= 1), std::abs() jest używane do obliczenia wartości bezwzględnej
        if (x0 > x1) {
            swap(x0, x1);
			swap(y0, y1);
        }
		dx = x1 - x0;
        dy = y1 - y0;

        if (dx == 0) {
            PutPixel(x0, y0, color);
            return;
        }

		float m = static_cast<float>(dy) / dx;
		float y = static_cast<float>(y0);

		for (int x = x0; x <= x1; x++) {
			PutPixel(x, static_cast<int>(round(y)), color);
			y += m;
		}
    }
	else { // Linia jest bardziej pionowa niż pozioma
        if (y0 > y1) {
            swap(x0, x1);
            swap(y0, y1);
        }
		dx = x1 - x0;
		dy = y1 - y0;

		if (dy == 0) {
			PutPixel(x0, y0, color);
			return;
		}

		float m_prime = static_cast<float>(dx) / dy;
		float x = static_cast<float>(x0);

		for (int y = y0; y <= y1; y++) {
			PutPixel(static_cast<int>(round(x)), y, color);
			x += m_prime;
		}
    }
}

void PrimitiveRenderer::DrawLineBresenham(const Point2D& p1, const Point2D& p2, Color color) const
{
	int x0 = p1.GetX();
	int y0 = p1.GetY();
	int x1 = p2.GetX();
	int y1 = p2.GetY();

	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);

	// Określamy kierunek kroku dla osi X i Y (+1 lub -1)
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	// Zmienna błędu (decyzyjna) – decyduje, kiedy przesunąć drugą współrzędną
	int err = dx - dy;

	while (true) {
		PutPixel(x0, y0, color);

		// Jeśli dotarliśmy do punktu końcowego, przerywamy pętlę
		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;

		// Krok wzdłuż osi X
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}

		// Krok wzdłuż osi Y
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void PrimitiveRenderer::DrawPolyline(const std::vector<Point2D>& points, Color color, bool closed) const
{
	if (points.size() < 2) return;

	// Łączymy kolejne punkty odcinkami
	for (size_t i = 0; i < points.size() - 1; ++i) {
		DrawLine(points[i], points[i + 1], color);
	}

	// Jeśli łamana ma być zamknięta, rysujemy odcinek łączący ostatni punkt z pierwszym
	if (closed && points.size() > 2) {
		DrawLine(points.back(), points.front(), color);
	}
}

void PrimitiveRenderer::DrawPolyline(const std::vector<LineSegment>& segments, Color color) const
{
	// Rysujemy każdy odcinek wchodzący w skład wektora
	for (const auto& segment : segments) {
		DrawLine(segment.GetStartPoint(), segment.GetEndPoint(), color);
	}
}

void PrimitiveRenderer::DrawTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const
{
	DrawLine(p1,p2,color);
	DrawLine(p1,p3,color);
	DrawLine(p2,p3,color);
}

void PrimitiveRenderer::DrawRectangle(const Point2D& p1, int width, int height, Color color) const
{
	int w = std::abs(width);
	int h = std::abs(height);

	int startX = (width < 0) ? p1.GetX() - w : p1.GetX();
	int startY = (height < 0) ? p1.GetY() - h : p1.GetY();

	Point2D p2(startX + w, startY);
	Point2D p3(startX + w, startY + h);
	Point2D p4(startX, startY + h);
	Point2D topLeft(startX, startY);

	DrawLine(topLeft, p2, color);
	DrawLine(p2, p3, color);
	DrawLine(p3, p4, color);
	DrawLine(p4, topLeft, color);
}

void PrimitiveRenderer::DrawCircle(const Point2D& center, int radius, Color color) const
{
	if (radius <= 0) return;

	float a, step;
	int x, y;

	step = 1.0f / radius;
	int x0 = center.GetX();
	int y0 = center.GetY();

	for (a = 0; a <= PI / 4; a += step) {
		x = static_cast<int>(radius * cos(a) + 0.5f);
		y = static_cast<int>(radius * sin(a) + 0.5f);

		// 4 symetrie podstawowe
		PutPixel(x0 + x, y0 + y, color);
		PutPixel(x0 - x, y0 + y, color);
		PutPixel(x0 + x, y0 - y, color);
		PutPixel(x0 - x, y0 - y, color);

		// 4 symetrie wynikające z zamiany x i y (ośmiokrotna symetria)
		PutPixel(x0 + y, y0 + x, color);
		PutPixel(x0 - y, y0 + x, color);
		PutPixel(x0 + y, y0 - x, color);
		PutPixel(x0 - y, y0 - x, color);
	}
}

void PrimitiveRenderer::DrawEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const
{
	if (radiusX <= 0 || radiusY <= 0) return;

	float a, step;
	int x, y;

	step = 1.0f / max(radiusX, radiusY);
	int x0 = center.GetX();
	int y0 = center.GetY();

	for (a = 0; a < PI / 2; a += step)
	{
		x = static_cast<int>(radiusX * cos(a) + 0.5f);
		y = static_cast<int>(radiusY * sin(a) + 0.5f);

		// 4 symetrie
		PutPixel(x0 + x, y0 + y, color);
		PutPixel(x0 - x, y0 + y, color);
		PutPixel(x0 + x, y0 - y, color);
		PutPixel(x0 - x, y0 - y, color);
	}
	// Dorysowanie skrajnych punktów osiowych, aby domknąć elipsę na krawędziach
	PutPixel(x0, y0 + radiusY, color);
	PutPixel(x0, y0 - radiusY, color);
	PutPixel(x0 + radiusX, y0, color);
	PutPixel(x0 - radiusX, y0, color);
}

// Zwraca orientację uporządkowanej trójki (p, q, r):
// 0 -> punkty współliniowe
// 1 -> zgodnie z ruchem wskazówek zegara (CW)
// 2 -> przeciwnie do ruchu wskazówek zegara (CCW)
int PrimitiveRenderer::Orientation(const Point2D& p, const Point2D& q, const Point2D& r) const
{
	long long val = static_cast<long long>(q.GetY() - p.GetY()) * (r.GetX() - q.GetX()) -
		static_cast<long long>(q.GetX() - p.GetX()) * (r.GetY() - q.GetY());

	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

// Sprawdza, czy punkt q leży na odcinku pr (przy założeniu współliniowości)
bool PrimitiveRenderer::OnSegment(const Point2D& p, const Point2D& q, const Point2D& r) const
{
	return q.GetX() <= std::max(p.GetX(), r.GetX()) && q.GetX() >= std::min(p.GetX(), r.GetX()) &&
		q.GetY() <= std::max(p.GetY(), r.GetY()) && q.GetY() >= std::min(p.GetY(), r.GetY());
}

// Zwraca true, jeśli odcinek s1 przecina się z odcinkiem s2
bool PrimitiveRenderer::DoSegmentsIntersect(const LineSegment& s1, const LineSegment& s2) const
{
	Point2D p1 = s1.GetStartPoint();
	Point2D q1 = s1.GetEndPoint();
	Point2D p2 = s2.GetStartPoint();
	Point2D q2 = s2.GetEndPoint();

	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, q2);
	int o3 = Orientation(p2, q2, p1);
	int o4 = Orientation(p2, q2, q1);

	// Przypadek ogólny: końce leżą po przeciwnych stronach drugiego odcinka
	if (o1 != o2 && o3 != o4)
		return true;

	// Przypadki szczególne (współliniowość)
	if (o1 == 0 && OnSegment(p1, p2, q1)) return true;
	if (o2 == 0 && OnSegment(p1, q2, q1)) return true;
	if (o3 == 0 && OnSegment(p2, p1, q2)) return true;
	if (o4 == 0 && OnSegment(p2, q1, q2)) return true;

	return false;
}

void PrimitiveRenderer::DrawPolygon(const std::vector<Point2D>& points, Color color) const
{
	// Wielokąt wymaga co najmniej 3 wierzchołków
	if (points.size() < 3) return;

	// Budujemy listę krawędzi zamykającą figurę
	std::vector<LineSegment> edges;
	edges.reserve(points.size());

	for (size_t i = 0; i < points.size(); ++i) {
		edges.emplace_back(points[i], points[(i + 1) % points.size()]);
	}

	// Delegujemy walidację i rysowanie do wersji przyjmującej wektor odcinków
	DrawPolygon(edges, color);
}

void PrimitiveRenderer::DrawPolygon(const std::vector<LineSegment>& segments, Color color) const
{
	size_t n = segments.size();
	if (n < 3) return;

	// 1. Sprawdzenie ciągłości łamanej (koniec odcinka i musi być początkiem odcinka i+1, a ostatni wracać do pierwszego)
	for (size_t i = 0; i < n; ++i) {
		Point2D endCurr = segments[i].GetEndPoint();
		Point2D startNext = segments[(i + 1) % n].GetStartPoint();
		if (endCurr.GetX() != startNext.GetX() || endCurr.GetY() != startNext.GetY()) {
			return; // Łamana nie jest ciągła lub nie jest zamknięta
		}
	}

	// 2. Sprawdzenie, czy niesąsiadujące krawędzie się przecinają (łamana wiązana)
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 2; j < n; ++j) {
			// Pomijamy parę pierwszej (0) i ostatniej (n - 1) krawędzi, bo dzielą wspólny wierzchołek startowy
			if (i == 0 && j == n - 1) continue;

			if (DoSegmentsIntersect(segments[i], segments[j])) {
				return; // Wykryto przecięcie! Przerywamy bez rysowania czegokolwiek
			}
		}
	}

	// 3. Jeśli wszystkie testy przeszły pomyślnie, rysujemy wielokąt
	for (const auto& edge : segments) {
		DrawLine(edge.GetStartPoint(), edge.GetEndPoint(), color);
	}
}

void PrimitiveRenderer::DrawFilledTriangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, Color color) const
{
	// Wyznaczamy prostokąt ograniczający (bounding box) trójkąta
	int minX = std::min({ p1.GetX(), p2.GetX(), p3.GetX() });
	int maxX = std::max({ p1.GetX(), p2.GetX(), p3.GetX() });
	int minY = std::min({ p1.GetY(), p2.GetY(), p3.GetY() });
	int maxY = std::max({ p1.GetY(), p2.GetY(), p3.GetY() });

	// Pomocnicza funkcja testująca orientację (edge function)
	auto edgeFunction = [](const Point2D& a, const Point2D& b, const Point2D& c) {
		return static_cast<long long>(c.GetX() - a.GetX()) * (b.GetY() - a.GetY()) -
			static_cast<long long>(c.GetY() - a.GetY()) * (b.GetX() - a.GetX());
		};

	// Przeszukujemy każdy piksel wewnątrz bounding boxa
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point2D pt(x, y);

			long long w1 = edgeFunction(p1, p2, pt);
			long long w2 = edgeFunction(p2, p3, pt);
			long long w3 = edgeFunction(p3, p1, pt);

			// Jeśli punkt leży po tej samej stronie wszystkich trzech krawędzi, to jest wewnątrz
			if ((w1 >= 0 && w2 >= 0 && w3 >= 0) || (w1 <= 0 && w2 <= 0 && w3 <= 0)) {
				PutPixel(x, y, color);
			}
		}
	}
}

void PrimitiveRenderer::DrawFilledRectangle(const Point2D& p1, int width, int height, Color color) const
{
	int w = std::abs(width);
	int h = std::abs(height);

	int startX = (width < 0) ? p1.GetX() - w : p1.GetX();
	int startY = (height < 0) ? p1.GetY() - h : p1.GetY();

	for (int y = startY; y < startY + h; ++y) {
		for (int x = startX; x < startX + w; ++x) {
			PutPixel(x, y, color);
		}
	}
}

void PrimitiveRenderer::DrawFilledCircle(const Point2D& center, int radius, Color color) const
{
	if (radius <= 0) return;

	int x0 = center.GetX();
	int y0 = center.GetY();

	// Dla każdego wiersza y wewnątrz promienia rysujemy poziomy odcinek (span)
	for (int dy = -radius; dy <= radius; ++dy) {
		// Z równania okręgu: dx = sqrt(R^2 - dy^2)
		int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));

		for (int dx_curr = -dx; dx_curr <= dx; ++dx_curr) {
			PutPixel(x0 + dx_curr, y0 + dy, color);
		}
	}
}

void PrimitiveRenderer::DrawFilledEllipse(const Point2D& center, int radiusX, int radiusY, Color color) const
{
	if (radiusX <= 0 || radiusY <= 0) return;

	int x0 = center.GetX();
	int y0 = center.GetY();

	double rx2 = static_cast<double>(radiusX) * radiusX;
	double ry2 = static_cast<double>(radiusY) * radiusY;

	// Dla każdego wiersza wewnątrz półosi pionowej obliczamy szerokość poziomą
	for (int dy = -radiusY; dy <= radiusY; ++dy) {
		double term = 1.0 - (static_cast<double>(dy) * dy) / ry2;
		if (term < 0.0) term = 0.0;

		int dx = static_cast<int>(std::sqrt(rx2 * term));

		for (int dx_curr = -dx; dx_curr <= dx; ++dx_curr) {
			PutPixel(x0 + dx_curr, y0 + dy, color);
		}
	}
}

void PrimitiveRenderer::DrawFilledPolygon(const std::vector<Point2D>& points, Color color) const
{
	size_t n = points.size();
	if (n < 3) return;

	// 1. Walidacja – sprawdzamy, czy wielokąt nie jest łamaną wiązaną
	std::vector<LineSegment> edges;
	edges.reserve(n);
	for (size_t i = 0; i < n; ++i) {
		edges.emplace_back(points[i], points[(i + 1) % n]);
	}

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 2; j < n; ++j) {
			if (i == 0 && j == n - 1) continue;
			if (DoSegmentsIntersect(edges[i], edges[j])) {
				return; // Wykryto przecięcie krawędzi – przerywamy działanie
			}
		}
	}

	// 2. Wyznaczenie zakresu pionowego (minY, maxY) dla linii skanujących
	int minY = points[0].GetY();
	int maxY = points[0].GetY();
	for (const auto& pt : points) {
		if (pt.GetY() < minY) minY = pt.GetY();
		if (pt.GetY() > maxY) maxY = pt.GetY();
	}

	// 3. Algorytm scanline z regułą parzystości (wiersz po wierszu od góry do dołu)
	for (int y = minY; y <= maxY; ++y) {
		std::vector<int> nodeX;

		for (size_t i = 0; i < n; ++i) {
			Point2D p1 = points[i];
			Point2D p2 = points[(i + 1) % n];

			int y1 = p1.GetY();
			int y2 = p2.GetY();
			int x1 = p1.GetX();
			int x2 = p2.GetX();

			// Warunek "<" oraz ">=" automatycznie rozwiązuje problem brzegowy wierzchołków na linii skanującej
			// (unikamy podwójnego liczenia wierzchołków przy zmianie kierunku krawędzi oraz ignorujemy krawędzie poziome)
			if ((y1 < y && y2 >= y) || (y2 < y && y1 >= y)) {
				int intersectX = static_cast<int>(std::round(x1 + static_cast<double>(y - y1) / (y2 - y1) * (x2 - x1)));
				nodeX.push_back(intersectX);
			}
		}

		// Sortujemy punkty przecięcia od lewej do prawej
		std::sort(nodeX.begin(), nodeX.end());

		// Wypełniamy odcinki między kolejnymi parami przecięć (nieparzyste -> parzyste)
		for (size_t i = 0; i + 1 < nodeX.size(); i += 2) {
			for (int x = nodeX[i]; x <= nodeX[i + 1]; ++x) {
				PutPixel(x, y, color);
			}
		}
	}

	// Dorysowanie konturu gwarantuje idealną gładkość krawędzi dolnych/górnych
	DrawPolygon(points, color);
}

Color PrimitiveRenderer::GetPixelColor(int x, int y) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return BLANK;

	return pixels[y * bufferWidth + x];
}

void PrimitiveRenderer::ClearBuffer(Color color) const
{
	std::fill(pixels.begin(), pixels.end(), color);
}

void PrimitiveRenderer::RenderBuffer() const
{
	for (int y = 0; y < bufferHeight; y++)
	{
		for (int x = 0; x < bufferWidth; x++)
		{
			DrawPixel(x, y, pixels[y * bufferWidth + x]);
		}
	}
}

void PrimitiveRenderer::FloodFill(int x, int y, Color color) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return;

	Color oldColor = GetPixelColor(x, y);

	auto sameColor = [](Color a, Color b)
		{
			return a.r == b.r &&
				a.g == b.g &&
				a.b == b.b &&
				a.a == b.a;
		};

	if (sameColor(oldColor, color))
		return;

	std::stack<Point2D> points;
	points.push(Point2D(x, y));

	while (!points.empty())
	{
		Point2D p = points.top();
		points.pop();

		int px = p.GetX();
		int py = p.GetY();

		if (px < 0 || px >= bufferWidth ||
			py < 0 || py >= bufferHeight)
			continue;

		if (!sameColor(GetPixelColor(px, py), oldColor))
			continue;

		PutPixel(px, py, color);


		points.push(Point2D(px + 1, py));
		points.push(Point2D(px - 1, py));
		points.push(Point2D(px, py + 1));
		points.push(Point2D(px, py - 1));
	}
}

void PrimitiveRenderer::BorderFill(int x, int y, Color fillColor, Color borderColor) const
{
	if (x < 0 || x >= bufferWidth ||
		y < 0 || y >= bufferHeight)
		return;

	auto sameColor = [](Color a, Color b)
		{
			return a.r == b.r &&
				a.g == b.g &&
				a.b == b.b &&
				a.a == b.a;
		};

	// Zabezpieczenie przed nieskończoną pętlą, gdy kolor wypełnienia jest taki sam jak kolor krawędzi
	if (sameColor(fillColor, borderColor))
		return;

	std::stack<Point2D> points;
	points.push(Point2D(x, y));

	while (!points.empty())
	{
		Point2D p = points.top();
		points.pop();

		int px = p.GetX();
		int py = p.GetY();

		if (px < 0 || px >= bufferWidth ||
			py < 0 || py >= bufferHeight)
			continue;

		Color currentColor = GetPixelColor(px, py);

		// Warunki zatrzymania z instrukcji: piksel ma już kolor wypełnienia lub kolor krawędzi
		if (sameColor(currentColor, fillColor) || sameColor(currentColor, borderColor))
			continue;

		PutPixel(px, py, fillColor);

		// Sąsiedztwo von Neumanna (N, S, W, E)
		points.push(Point2D(px, py - 1)); // N
		points.push(Point2D(px, py + 1)); // S
		points.push(Point2D(px - 1, py)); // W
		points.push(Point2D(px + 1, py)); // E
	}
}