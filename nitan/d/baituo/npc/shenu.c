// Code of ShenZhou
// shenu.c 蛇奴
// maco

/***************************************************************

breed                : 現在可學poison的極限
new_breed        : 最新一次培養怪蛇成功後，可學poison的極限
new_breed_time        : 最新一次開始培養怪蛇的時間
checked_snake        : 是否檢查過這次的怪蛇？

***************************************************************/
#include <ansi.h>

inherit NPC;

int ask_snake();
int ask_guaishe();
int do_order(string);

void create()
{
        set_name("蛇奴", ({ "she nu" ,"nu"}));
        set("long", "他是負責看管歐陽世家莊蛇場的蛇奴，擔當替莊主、少主養育怪蛇的事務。\n");
        set("gender", "男性");
        set("title", "歐陽世家莊");
        set("age", 35);

        set_skill("hand", 30);
        set_skill("shexing-diaoshou", 30);
        set_skill("dodge", 20);
        set_skill("parry", 30);
        set_skill("force", 20);
        map_skill("hand","shexing-diaoshou");
        map_skill("dodge","chanchubu");
        prepare_skill("hand","shexing-diaoshou");

        set("str", 28);
        set("int", 21);
        set("con", 27);
        set("dex", 21);

        set("max_neili", 200);
        set("jiali", 10);
        set("combat_exp", 10000);

        set("attitude", "peaceful");
        set("shen_type", -1);
        set("inquiry", ([
                "蛇" : (: ask_snake :),
                "snake" : (: ask_snake :),                
                "怪蛇" : (: ask_guaishe :),
                "guaishe" : (: ask_guaishe :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_order", "order");
}

int ask_snake()
{
        object me, snake;
        int time, poison, breed, new_breed;

        me = this_player();

        poison = (int)me->query_skill("poison",1);
        breed=query("baituo/breed", me);
        new_breed=query("baituo/new_breed", me);

        if( query("family/family_name", me) != "歐陽世家"){
                command("say "+RANK_D->query_rude(me)+"想打聽咱們的蛇兒，莫非動着什麼歪腦筋？");
                return 1;
        }

        if( query("family/master_name", me) != "歐陽鋒"){
                command("say 場子裏的蛇都是莊主和少主所飼養的。");
                return 1;
        }

        if( !query("baituo/new_breed_time", me) && !query("baituo/checked_snake", me)){
                command("say 場子裏沒有少主養的蛇，您是也想養些麼？");
                return 1;
        }

        if( query("baituo/checked_snake", me)){
                command("say 少主上次培育的蛇種已有結果，是否要再捉新的品種來改良？");
                return 1;
        }

        time=time()-query("baituo/new_breed_time", me);

        if(time < 600) {
                command("say 少主前次捉回來的蛇羣，小的日日夜夜都用心看顧，就等它們繁殖了。");
                return 1;
        }

        if(time < 1200) {
                command("say 少主前次捉回來的蛇已經下蛋了，想必近日便會孵化。");
                return 1;
        }

        command("say 小蛇已經出生了，小的這就去把它帶來。");
        message_vision("\n蛇奴匆匆忙忙地退了下去。\n", me);
        
        this_object()->move("/d/baituo/temproom");

        remove_call_out("bring_snake");
        call_out("bring_snake", 3, me);
        return 1;
}

void bring_snake(object me)
{
        object snake;
        int poison, breed, new_breed;
        string result;

        poison = (int)me->query_skill("poison",1);
        breed=query("baituo/breed", me);
        breed = breed*4/5 + random(breed/5);
        new_breed=query("baituo/new_breed", me);

        if( new_breed > poison+10 )  new_breed = poison + 10; 
        if( new_breed > 800 ) new_breed = 800;

        this_object()->move("/d/baituo/shechang");

        snake = new("/d/baituo/npc/new_snake");

        if( new_breed > poison ) {
                snake->set_name("小怪蛇", ({ "guai she", "she", "snake" }) );
                snake->set_color("$HIW$");
                snake->set("long",
                "一條銀鱗閃閃的小蛇，形狀怪異，是歐陽世家少主"+me->name()+"第"
                +chinese_number(query("baituo/manage", me))+"次培養出的蛇種。\n"
                );
                if( breed >= 600 )
                result = HIW"這條怪蛇的毒性猛惡一如以往，可見你對蛇毒的掌握，已然純熟如意。\n"NOR;
                else if( new_breed > breed ) 
                result = HIY"你成功地培養出了毒性更勝原種的怪蛇！\n"NOR
                + "如今，你對掌握毒物的法門領會更多，自信已有能力將毒技鑽研至"+chinese_number(new_breed)+"級。\n";
                else result = "雖然你培養出了怪蛇，但是神態不如以前的品種猙獰，想必毒性有所不及。\n";
        }
        else if( new_breed >= 400 ) {
                snake->set_name("小怪蛇", ({ "guai she", "she", "snake" }) );
                snake->set_color("$HIW$");
                snake->set("long",
                "一條銀鱗閃閃的小蛇，形狀怪異，是歐陽世家少主"+me->name()+"第"
                +chinese_number(query("baituo/manage", me))+"次培養出的蛇種。\n"
                );
                result = "雖然你培養出了怪蛇，但是以你的使毒本領而言，這等毒性的怪蛇稱不上突破，僅是增生怪蛇數量而已。\n";
        }
        else {
                snake->set_name("小毒蛇", ({ "snake", "she"}) );
                snake->set("long",
                "一條三角尖頭的小蛇，是歐陽世家少主"+me->name()+"第"
                +chinese_number(query("baituo/manage", me))+"次培養出的蛇種。\n"
                );
                if( !breed || breed == 0 )
                result = "這條毒蛇並無特異之處，看來這次培養的蛇種不甚成功。\n";
                else if( new_breed > breed ) 
                result = "你仔細檢視，覺得這條蛇的毒性雖然勝過上回培養的品種，然而依舊不夠理想。\n";
                else result = "你仔細端詳，卻見這條毒蛇毫無特異之處，看來毒性反而比從前弱了。\n";
        }

        message_vision("\n過了一會兒，蛇奴走了出來。\n", me);
        command("say 這是最近養育的小蛇中毒性最強的一，請少主過目。");
        message_vision("一條"+snake->name()+"蜿蜒地遊了過來。\n", me);

        snake->move(environment(me));
        snake->set_leader(me);
        set("who_breed",query("id",  me), snake);
        set("sk_poison", new_breed, snake);

        write(result);

        log_file("test/breed_snake",
                sprintf("%s(%s) 第%d次培養結果：%s(毒性%d) on %s \n", 
                me->name(),query("id", me),query("baituo/manage", me),snake->name(),new_breed,ctime(time())));

        if(new_breed > breed) {
                set("baituo/breed", new_breed, me);
                addn("baituo/success_breed", 1, me);
                if( me->query_skill("training") < 800 )
                        me->improve_skill("training", new_breed*50 );
                if( me->query_skill("poison") < 800 )
                        me->improve_skill("poison", new_breed*50 );
        }
        set("baituo/checked_snake", 1, me);
        delete("baituo/new_breed", me);
        delete("baituo/new_breed_time", me);

        return;
}

int ask_guaishe()
{
        object me;
        int num;
        me = this_player();
        num=query("baituo/snake_amount", me);

        if( query("family/family_name", me) != "歐陽世家"){
                command("say "+RANK_D->query_rude(me)+"想打聽咱們歐陽世家的怪蛇，莫非動着什麼歪腦筋？");
                return 1;
        }

        if( query("family/master_name", me) != "歐陽鋒"){
                command("say 莊主和少主費盡心思，以數種最毒之蛇相互雜交，才產下這些毒中之毒的怪蛇。");
                return 1;
        }
        if ( num < 1)
                command("say 現下場子裏沒有少主養的怪蛇。");
        else command("say 少主養在場子裏的怪蛇，一共有"+chinese_number(num)+"條。");

        if ( num > 10 )
        command("admire"+query("id", me));
        return 1;
}

int do_order(string arg)
{
        object me, room;
        int flag;
        me = this_player();
        
        if( query("family/family_name", me) != "歐陽世家")return 0;

        room = load_object("/d/baituo/shegu1");

        if( query("defense", room))flag=1;
        
        if ( arg == "defense") {

                if( flag ) return notify_fail("蛇谷入口已經由毒氣封住了。\n");

                if( query("family/master_name", me) != "歐陽鋒"){
                        message_vision(CYN"$N向蛇奴下令：放出密窖中的蛇毒，封住蛇谷的入口！\n"NOR, me);
                        command("bored"+query("id", me));
                        command("say 哼，要不要封谷，你我都做不了主！");
                        return 1;
                }

                message_vision(CYN"$N向蛇奴下令：放出密窖中的蛇毒，封住蛇谷的入口！\n"NOR, me);
                message_vision("蛇奴恭恭敬敬地答應，退到蛇場一角，啟動了釋放密窖毒氣的機關。\n", me);
                message_vision(HIR"\n你聽到蛇場外傳來一陣嘶嘶輕響……\n"NOR, me);
                
                message("vision", HIR"你突然聽到一陣嘶嘶輕響，一片血紅色的霧氣緩緩從土地下噴出，漸漸佈滿了整個谷口……\n\n"NOR,room );
                set("defense", 1, room);
                command("say 少主，辦妥了！");
        }

        else if( arg == "remove" ) {
                if( !flag ) return notify_fail("蛇谷入口現在本就沒有毒氣。\n");


                if( query("family/master_name", me) != "歐陽鋒"){
                        message_vision(CYN"$N向蛇奴下令：停止從密窖釋放毒氣，開放蛇谷的入口！\n"NOR, me);
                        command("kick"+query("id", me));
                        command("say 你想害死我不成？沒有莊主下令，誰敢擅開蛇谷？");
                        return 1;
                }
                message_vision(CYN"$N向蛇奴下令：停止從密窖釋放毒氣，開放蛇谷的入口！\n"NOR, me);
                message_vision(CYN"$N嘿嘿冷笑，説道："+RANK_D->query_self_rude(me)+"要讓那些自居名門正派的人物，送上谷來給咱們蛇兒果腹！\n"NOR, me);

                command("fear"+query("id", me));
                message_vision("蛇奴面有難色，但是被$N斜眼一瞪，還是戰戰兢兢地退開，解除了機關。\n", me);
                message_vision(WHT"\n你聽到蛇場外傳來一陣嘶嘶輕響，接着很快又安靜下來。\n"NOR, me);
                message("vision", WHT"你突然聽到一陣嘶嘶輕響，封鎖在蛇谷前的紅霧慢慢消散，土裏也沒有霧氣再冒出來。\n不一會兒，煙消雲散，蛇谷的入口完全呈現在眼前。\n\n"NOR,room );
                delete("defense", room);

                command("say 少主，小的依您吩咐，關了毒氣，但莊主要問起來，您可得擔待住……");
        }

        else return notify_fail("你要對蛇奴下什麼命令？ (defense or remove) \n");

        return 1;
}