// Room: /d/yanping/mangdangshan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "茫盪山");
        set("long", @LONG
茫盪山清涼世界，風物絕佳。步移景異，所見或石壁陡峭、或深谷
懸崖；山澗小溪忽在道旁潺潺低唱，忽而在斷崖前跌落為瀑布；那遠近
林中不時傳出的鳥叫聲和那宛囀不絕的蟬鳴更是增添了幽靜、深遠的感
覺。舉目四顧，但見風煙俱靜，天山共色，頓覺心胸開闊、神清氣爽。
LONG );
        set("exits", ([
                "east" : __DIR__"gubao",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1480);
        set("coor/y", -6110);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}