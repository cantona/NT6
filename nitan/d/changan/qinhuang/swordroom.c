inherit ROOM;
int do_xue(string arg);
void create()
{
    set("short", "劍俑");
        set("long", @LONG
這裡的陶俑手裡都拿著劍，擺著各種姿勢，神態各異。
LONG );
    set("exits", ([
        "east" : __DIR__"shidao2",
    ]));
    setup();
}
void init()
{
    add_action("do_xue", "xue");
}


int do_xue(string arg)
{
    object me;
    me = this_player();
    if ( !arg || ( arg != "俑" ) )
        return notify_fail("什麼？\n");
    if ( (int)me->query_skill("literate", 1) < 1)
        return notify_fail("你是個文盲，先學點文化(literate)吧。\n");
    if( query("unarmed", me))return notify_fail("你已經學過拳俑了。\n");
    if( query("hammer", me))return notify_fail("你已經學過錘俑了。\n");
    if( query("club", me))return notify_fail("你已經學過棍俑了。\n");
    if( query("blade", me))return notify_fail("你已經學過刀俑了。\n");
    if( query("whip", me))return notify_fail("你已經學過鞭俑了。\n");
    if( query("staff", me))return notify_fail("你已經學過杖俑了。\n");
    if( query("throwing", me))return notify_fail("你已經學過箭俑了。\n");
    if( query("axe", me))return notify_fail("你已經學過斧俑了。\n");
    me->receive_damage("jing", 1000);
    message_vision("$N開始模仿學習這些秦俑的各種動作。\n", me);
    if ( (int)me->query_skill("sword", 1) < 851)
    {
        me->improve_skill("sword", me->query_int());
        set("sword", 1, me);
        return 1;
    }
    write("你對著秦俑瞧了一回兒，發現已經沒有什麼好學的了。\n");
    return 1;
}