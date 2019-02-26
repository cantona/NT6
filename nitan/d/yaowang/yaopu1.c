inherit ROOM;

void create()
{
        set("short", "藥圃");
        set("long", @LONG
這裏是一處很大的藥苗圃，遍地開着各色怪異的小花，空氣
裏瀰漫着香臭混雜的怪味道。
LONG
        );
        set("exits", ([
  "northeast" : __DIR__"xiaodao5",
  "west" : __DIR__"lu2",
  "south" : __DIR__"xiaodao4",
]));

        set("objects", ([
                "/kungfu/class/yaowang/xue" : 1,
        ]));
        
        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
