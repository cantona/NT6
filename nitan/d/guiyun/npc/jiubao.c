// Npc: /d/guiyun/npc/jiubao.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        set_name("酒保", ({ "jiu bao", "jiubao", "jiu", "bao", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "這位酒保正跑前跑後地忙著。\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
        set("inquiry", ([
                "name"   : "不敢不敢，小的叫張小泉，是在太湖邊上長大的。",
                "rumors" : "歸雲莊的弟子們總來這裡，有時候談到桃花島，都流露出向往的神情。",
                "here"   : "這裡是太湖邊，往北走就可以看到歸雲莊了。",
                "桃花島" : "是東海上的小島，往杭州的東南走，到海邊看能不能雇船吧？",
                "生意"   : "因為歸雲莊的弟子們總來照顧小店的生意，所以還算不錯。",
                "歸雲莊" : "向北走就能看到。那裡的莊主姓陸，平時難得見到。",
                "蘇州" : "在揚州的東南邊，出揚州東門去找。",
                "杭州" : "在蘇州的東南邊。",
                "襄陽" : "從揚州往西走就能走到。",
                "成都" : "從襄陽往西再轉西南。",
                "少林" : "在河南少室山，從揚州往北可以走到。",
                "少林寺" : "在河南少室山，從揚州往北可以走到。",
                "少林派" : "在河南少室山，從揚州往北可以走到。",
                "武當" : "在湖北境內，出了揚州往南面走吧。",
                "武當山" : "在湖北境內，出了揚州往南面走吧。",
                "武當派" : "在湖北境內，出了揚州往南面走吧。",
                "星宿" : "在天山西邊，從揚州往西去找。",
                "星宿海" : "在天山西邊，從揚州往西去找。",
                "星宿派" : "在天山西邊，從揚州往西去找。",
                "明教" : "在昆侖山東邊，從揚州往西走。",
                "光明頂" : "在昆侖山東邊，從揚州往西走。",
                "慕容" : "在姑蘇燕子圬，去蘇州找找看吧。",
                "姑蘇慕容" : "在姑蘇燕子圬，去蘇州找找看吧。",
                "歸雲莊" : "在太湖邊上，從蘇州往南走。",
                "丐幫" : "這可是個秘密呀。",
                "昆侖" : "在遙遠的西域，一直往西走吧。",
                "昆侖山" : "在遙遠的西域，一直往西走吧。",
                "昆侖派" : "在遙遠的西域，一直往西走吧。",
                "古墓" : "在終南山，從揚州向北再折向西南吧。",
                "終南山" : "從揚州向北再折向西南吧。",
                "大理" : "在大宋的南邊，所以要從揚州往南走。",
                "華山" : "在陝西境內，從揚州城西向北走可以到達。",
                "猴爪山" : "在川湘交界處，從揚州向南再向西行。",
                "鐵掌山" : "在川湘交界處，從揚州向南再向西行。",
                "鐵掌幫" : "在川湘交界處，從揚州向南再向西行。",
                "峨嵋山" : "在川西，從成都南門往偏西走。",
                "峨嵋派" : "在川西，從成都南門往偏西走。",
                "峨嵋" : "在川西，從成都南門往偏西走。",
        ]) );
        setup();
}

void init()
{        
        object ob;

        ::init();
        if (base_name(environment()) != query("startroom")) return;
        if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int accept_object(object who, object ob)
{
        object zhanggui;

        if( query("money_id", ob)){
                if (!objectp(zhanggui = present("zhang gui", environment()))) {
                        zhanggui = new(__DIR__"zhanggui");
                        zhanggui->move(environment());
                }
                tell_object(who, "酒保道：“我帶你去掌櫃那裡付帳。”\n");
                tell_object(who, "你跟著酒保來到櫃台前，把錢交給掌櫃。\n");
                return zhanggui->accept_object(who, ob);
        }
        return 0;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("酒保對$N冷笑道：“別裝腔作勢啦，象你這種扮兇巴巴妄圖吃飯不付錢的家伙我見多了，省省吧。”\n", ob);
        message_vision("$N心中納悶：“我這番齷齪心思怎麼全被他說中了？”\n", ob);
}

void greeting(object ob)
{
        if (!present(ob, environment())) return;
        say( "酒保笑咪咪地說道：這位" + RANK_D->query_respect(ob) + "，快進來坐。\n");
}

void unconcious()
{
        say( "酒保大喊一聲：“我不行了，快來接班！”\n");
        say( "結果從櫃台後面又鑽出一個酒保來，說：“沒問題，交給我吧。”\n");
        say( "前一個酒保快快樂樂地離開了。\n");
        reincarnate();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
}

void die()
{
        unconcious();
}

void relay_emote(object me,string arg)
{
        command(arg+""+query("id", me));
}
