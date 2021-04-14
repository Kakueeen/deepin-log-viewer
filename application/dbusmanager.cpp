/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     zyc <zyc@uniontech.com>
*
* Maintainer:  zyc <zyc@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "dbusmanager.h"

#include <QDebug>

bool DBusManager::isGetedKlu = false;
QString DBusManager::isklusystemName = "";
QDBusInterface *DBusManager::m_TabletInterFace = nullptr;
/**
 * @brief DBusManager::DBusManager
 * dbus接口获取工具类
 * @param parent
 */
DBusManager::DBusManager(QObject *parent) : QObject(parent)
{

}

DBusManager::~DBusManager()
{
    delete m_TabletInterFace;
}

/**
 * @brief DBusManager::getSystemInfo
 * 通过dBus接口获取系统是否为klu/pangu/panguV
 * @return 返回klu/pangu/panguV或者空,如果没有此dbus接口也返回空,返回空表示不是klu/pangu/panguV
 */
QString DBusManager::getSystemInfo()
{
    if (!isGetedKlu) {
        isklusystemName =  QDBusInterface("com.deepin.system.SystemInfo", "/com/deepin/system/SystemInfo", "com.deepin.system.SystemInfo", QDBusConnection::systemBus())
                           .property("ProductName")
                           .toString();
        isGetedKlu = true;
    }
    return  isklusystemName;
}

/*!
 * \~chinese \brief DBusManager::TableInterFace 获取虚拟键盘dbus接口
 * \~chinese \return 虚拟键盘dbus接口
 */
QDBusInterface *DBusManager::TableInterFace()
{
    m_TabletInterFace = new QDBusInterface("com.deepin.im", "/com/deepin/im", "com.deepin.im", QDBusConnection::sessionBus());
    return m_TabletInterFace;
}
