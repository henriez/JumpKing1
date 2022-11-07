#pragma once

class Ente {
public:
	Ente() {}
	virtual ~Ente() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
};