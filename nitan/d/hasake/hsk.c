// hsk.c 哈薩克帳篷
inherit ROOM;
void create()
{
        set("short", "哈薩克帳篷");
        set("long", @LONG
這是哈薩克族人居住的帳篷，方圓兩三丈，正中以一粗木做主樑，四
周用小木樁圍成一圈，從主樑拉牛皮帳篷過木樁再釘于地上。草原上居住
的民族都喜歡這種帳篷，方便簡單。因蒙古族人數最多，所以又統稱這種
帳篷為“蒙古包”。
LONG);
        set("exits", ([
            "west" : __DIR__"majiu",
            "northeast" : __DIR__"caoyuan",
   //         "north" : __DIR__"caoyuan1",
            "southwest" : __DIR__"room-che",
         ]));
         set("objects", ([
                    __DIR__"npc/hasake1" : 1,
                    __DIR__"obj/cheese" : 1,
        ]));        
        setup();
        replace_program(ROOM);
}