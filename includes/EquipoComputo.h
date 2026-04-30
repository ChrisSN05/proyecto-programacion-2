#ifndef PROYECTO_PROGRAMACION_2_SPIM_EQUIPOCOMPUTO_H
#define PROYECTO_PROGRAMACION_2_SPIM_EQUIPOCOMPUTO_H


#include "Equipo.h"
#include <string>

class EquipoComputo final : public Equipo {
protected:
    void aplicarMantenimientoEspecifico() override;

public:
    EquipoComputo(const std::string &codigo,
                  const std::string &nombre,
                  int criticidad,
                  int estado);

    void degradar() override;

    std::string obtenerTipo() const override;

    void revisarSoftware();
};

#endif
