// Room: /yangzhou/baitataji.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","白塔塔基");
        set("long",@LONG
白塔，在蓮花橋側蓮性寺內，一稱喇嘛塔，仿北京北海喇嘛塔式，
其形如錐，高入雲表。塔基建台53級，台上造塔，塔身中空，其外層拾
級而上，加青銅纓絡鎏金塔鈴，最上簇鎏金頂。每值晴日當空，塔頂金
光四射，與南門外文峯塔遙相對峙，稱為邗上巨觀。揚州民間有“南門
寶塔北門錐”之説。
    白塔塔基。象徵佛教“五十三參”的五十三級塔下築台，石級平台
南嵌“白塔晴雲”石額。
LONG );
        set("exits", ([
                "north" : __DIR__"lianxingsi",
                "up"    : __DIR__"baitafokan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 50);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}