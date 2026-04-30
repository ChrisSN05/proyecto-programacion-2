#ifndef PROYECTO_PROGRAMACION_2_SPIM_EQUIPOLABORATORIO_H
#define PROYECTO_PROGRAMACION_2_SPIM_EQUIPOLABORATORIO_H


#include "Equipo.h"
#include <string>

class EquipoLaboratorio final : public Equipo {
protected:
    void aplicarMantenimientoEspecifico() override;

public:
    EquipoLaboratorio(const std::string &codigo,
                      const std::string &nombre,
                      int criticidad,
                      int estado);

    void degradar() override;

    std::string obtenerTipo() const override;
};

#endif
