/*
  Copyright (C) 2015 François KUBLER
  Contact: François Kubler <francois@kubler.org>
  All rights reserved.

    This file is part of StrasbourgParking.

    StrasbourgParking is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    StrasbourgParking is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DataSource.h"

const QString DataSource::source1 = QString("http://carto.strasmap.eu/remote.amf.json/Parking.geometry");
const QString DataSource::source2 = QString("http://carto.strasmap.eu/remote.amf.json/Parking.status");

DataSource::DataSource(QObject *parent) : QObject(parent)
{
    this->m_req1 = new JSONRequest(this);
    this->m_req2 = new JSONRequest(this);

    QObject::connect(this->m_req1, &JSONRequest::documentReady, this, &DataSource::emitListReady);
    QObject::connect(this->m_req1, &JSONRequest::networkError, this, &DataSource::emitNetworkError);
    QObject::connect(this->m_req1, &JSONRequest::jsonParsingError, this, &DataSource::handleJsonParsingError);

    QObject::connect(this->m_req2, &JSONRequest::documentReady, this, &DataSource::emitDataReady);
    QObject::connect(this->m_req2, &JSONRequest::networkError, this, &DataSource::emitNetworkError);
    QObject::connect(this->m_req2, &JSONRequest::jsonParsingError, this, &DataSource::handleJsonParsingError);
}

DataSource::~DataSource()
{
    delete this->m_req1;
    delete this->m_req2;
}



void DataSource::getList() const
{
    this->m_req1->request(DataSource::source1);
}

void DataSource::getData() const
{
    this->m_req2->request(DataSource::source2);
}


void DataSource::emitListReady(const QJsonDocument &d)
{
    emit listReady(d);
}

void DataSource::emitDataReady(const QJsonDocument &d)
{
    emit dataReady(d);
}

void DataSource::emitNetworkError(const QNetworkReply::NetworkError &errcode)
{
    emit networkError(errcode);
}

void DataSource::handleJsonParsingError(const QString &err)
{
    qDebug() << err;
}
