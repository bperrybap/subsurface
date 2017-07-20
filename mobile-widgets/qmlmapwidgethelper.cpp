// SPDX-License-Identifier: GPL-2.0
#include <QDebug>

#include "qmlmapwidgethelper.h"
#include "core/dive.h"
#include "core/divesite.h"
#include "qt-models/maplocationmodel.h"

MapWidgetHelper::MapWidgetHelper(QObject *parent) : QObject(parent)
{
	m_mapLocationModel = new MapLocationModel(this);
	connect(m_mapLocationModel, SIGNAL(selectedLocationChanged(MapLocation *)),
	        this, SLOT(selectedLocationChanged(MapLocation *)));
}

void MapWidgetHelper::centerOnDiveSite(struct dive_site *ds)
{
	if (!dive_site_has_gps_location(ds)) {
		QMetaObject::invokeMethod(m_map, "deselectMapLocation");
		return;
	}
	MapLocation *location = m_mapLocationModel->getMapLocationForUuid(ds->uuid);
	QMetaObject::invokeMethod(m_map, "centerOnMapLocation", Q_ARG(QVariant, QVariant::fromValue(location)));
}

void MapWidgetHelper::reloadMapLocations()
{
	struct dive_site *ds;
	int idx;
	m_mapLocationModel->clear();
	QVector<MapLocation *> locationList;

	for_each_dive_site(idx, ds) {
		if (!dive_site_has_gps_location(ds))
			continue;
		const qreal longitude = ds->longitude.udeg / 1000000.0;
		const qreal latitude = ds->latitude.udeg / 1000000.0;
		locationList.append(new MapLocation(ds->uuid, QGeoCoordinate(latitude, longitude)));
	}
	m_mapLocationModel->addList(locationList);
}

void MapWidgetHelper::selectedLocationChanged(MapLocation *location)
{
	qDebug() << location;
}