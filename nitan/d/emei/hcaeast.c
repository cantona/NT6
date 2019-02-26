inherit ROOM;

void create()
{
        set("short", "東側殿");
        set("long", @LONG
這裏是金頂華藏庵東側殿，是接待香客及來賓的地方。殿內擺着
幾張桌子，桌旁圍放數把椅子。牆上懸着幾幅字畫，牆邊一排書架，
架上擺滿經書。有幾位進香客正在品茶養神，欣賞牆上的字畫或翻閲
架上的經書。還有兩個二十來歲的姑娘在向一位師太打聽有關出家的
事。一個十來歲的小師太正在忙前忙後招待客人。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/he" : 1,
                CLASS_D("emei") + "/wenhui" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"hcazhengdian", 
        ]));
        set("coor/x", -550);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}