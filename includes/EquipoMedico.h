#ifndef PROYECTO_PROGRAMACION_2_SPIM_EQUIPOMEDICO_H
#define PROYECTO_PROGRAMACION_2_SPIM_EQUIPOMEDICO_H


#include "Equipo.h"
#include <string>

class EquipoMedico final : public Equipo {
protected:
    void aplicarMantenimientoEspecifico() override;

public:
    EquipoMedico(const std::string &codigo,
                 const std::string &nombre,
                 int criticidad,
                 int estado);

    void degradar() override;

    std::string obtenerTipo() const override;

    void calibrarSensores();
};

#endif