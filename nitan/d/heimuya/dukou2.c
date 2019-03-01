inherit RIVER;

void create()
{
        set ("short", "龍門渡口");
        set ("long", @LONG
渡口前就是洶湧澎湃的黃河 (river)了。濁流滾滾，泥沙
俱下，聲震數裡。兩岸渡船來來往往，在波谷中穿行，甚為兇
險。過了黃河，就是陝西了。
LONG);
        set("to", __DIR__"dukou1");
        set("exits", ([
                "southwest" : "/d/huanghe/huanghe_1",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu",
        }));

        set("outdoors", "heimuya");
        setup();
        replace_program(RIVER);
}
