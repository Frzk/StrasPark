.pragma library

.import QtQuick.LocalStorage 2.0 as SQL


function getDatabase()
{
    var db = SQL.LocalStorage.openDatabaseSync("StrasPark", "1.0", "StrasPark app.", 50000);

    var sql ="CREATE TABLE IF NOT EXISTS parkinglots (";
    sql += "id INTEGER PRIMARY KEY,";
    sql += " name TEXT,";
    sql += " lng TEXT,";
    sql += " lat TEXT,";
    sql += " isRelay BOOLEAN,";
    sql += " isFavorite BOOLEAN"
    sql += ")";

    db.transaction(
        function(tx)
        {
            tx.executeSql(sql);
        }
    );

    return db;
}

function count()
{
    var db = getDatabase();
    var r = 0;
    var sql = "SELECT COUNT(id) AS nb FROM parkinglots";

    db.readTransaction(
        function(tx)
        {
            var result = tx.executeSql(sql);
            if(result.rows.length > 0)
                r = result.rows.item(0).nb;
        }
    );

    return parseInt(r);
}

function list()
{
    var db = getDatabase();
    var result = null;

    var sql = "SELECT * FROM parkinglots ORDER BY isFavorite DESC, name ASC";

    db.readTransaction(
        function(tx)
        {
            result = tx.executeSql(sql);
        }
    );

    return result;
}

function insert(data)
{
    try
    {
        var db = getDatabase();

        //FIXME: isFavorite
        var sql = "INSERT OR REPLACE INTO parkinglots (id, name, lng, lat, isRelay, isFavorite)";
        sql += " VALUES(?, ?, ?, ?, ?, 0)";

        //var data = [5, 'Nouveau Parking Lixenbuhl', '7.325435', '42.43534564', 0, 1];

        db.transaction(
            function(tx)
            {
                var r = tx.executeSql(sql, data);

                if(r.rowsAffected > 0)
                {
                    //console.log(data[1], "(", data[0], ") inserted/updated.");
                }
                else
                {
                    //FIXME
                }
            }
        );
    }
    catch(e)
    {
        console.log(e);
    }
}

function markAsFavorite(index, isFav)
{
    try
    {
        var db = getDatabase();

        var sql = "UPDATE parkinglots SET isFavorite=? WHERE id=?";
        var data = [isFav, index];

        db.transaction(
            function(tx)
            {
                var r = tx.executeSql(sql, data);

                if(r.rowsAffected > 0)
                    console.log("Successfully updated.");
                else
                    //FIXME
                    console.log("Update failed.");
            }
        );
    }
    catch(e)
    {
        console.log(e);
    }
}

function _dropTable(db)
{
    var sql = "DROP TABLE parkinglots;"

    try
    {
        db.transaction(
            function(tx)
            {
                tx.executeSql(sql);
            }
        );
    }
    catch(e)
    {
    }
}
