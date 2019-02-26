inherit ROOM;

void create()
{
        set("short", "沙灘");
        set("long", @LONG
一片金黃色的沙灘，無邊無際的大海就在眼前了。碧藍的的海水上面湧動的
潔白的浪花，海面飄着輕輕的薄霧。茫茫的大海上沒有一點帆影，極目遠眺，海
天交界處濛濛一片，分不出哪裏是海，哪裏是天。海風清涼，略有點鹹味，海面
微微泛着波浪。
LONG );

        set("exits", ([
                "west" : "/d/tulong/tulong/haian",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/liuyun" : 1,
        ]));

        set("outdoors", "tulong");
        setup();
}
