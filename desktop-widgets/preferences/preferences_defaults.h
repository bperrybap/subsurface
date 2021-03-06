// SPDX-License-Identifier: GPL-2.0
#ifndef PREFERENCES_DEFAULTS_H
#define PREFERENCES_DEFAULTS_H

#include "abstractpreferenceswidget.h"
#include "core/pref.h"

namespace Ui {
	class PreferencesDefaults;
}

class PreferencesDefaults : public AbstractPreferencesWidget {
	Q_OBJECT
public:
	PreferencesDefaults();
	~PreferencesDefaults();
	void refreshSettings();
	void syncSettings();
public slots:
	void on_chooseFile_clicked();
	void on_btnUseDefaultFile_toggled(bool toggled);
	void on_localDefaultFile_toggled(bool toggled);
	void on_ffmpegFile_clicked();
	void on_extractVideoThumbnails_toggled(bool toggled);

private:
	Ui::PreferencesDefaults *ui;
};


#endif
