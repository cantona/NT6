//ROOM: /d/yanziwu/bingqi.c

inherit ROOM;

void create()
{
        set("short", "神兵閣");
        set("long",@LONG
這裏就是慕容家藏兵之所。這裏擺設着慕容家歷代祖先縱橫江湖所
用的兵器，以及他們百戰獲得的神兵。所有的這些擺設已顯得相當古舊
了。在閣樓角，落堆放着一摞摞的尋常兵器。
LONG );
        set("exits", ([
                "north": __DIR__"chixia",
        ]));
        set("objects", ([
                "/clone/weapon/changjian": random(2),
                "/clone/weapon/changbian": random(2),
                "/clone/weapon/changqiang": random(2),
                "/clone/weapon/gangdao": random(2),
                "/clone/weapon/dagger": random(2),
                "/clone/weapon/gangzhang": random(2),
                "/clone/weapon/jili": random(2),
                "/clone/weapon/hammer": random(2),
                "/clone/weapon/lianzi": random(2),
                "/clone/weapon/qimeigun": random(2),
        ]));
        set("coor/x", 820);
        set("coor/y", -1860);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}