#include <ansi.h>
#include <command.h>
inherit F_DBASE;
#define DOOM_PATH "/d/llszhuang"
string *additional_room = ({
        });
string *additional_npc = ({
        });

//所有可能的方向
string *all_dir =       ({      "north","northeast","northwest","south",
                                "southwest","southeast","east","west",    
                                "up","down","enter","out",
                                "northup","northdown","eastup","eastdown",
                                "westup","westdown","southup","southdown",
                        });

int i,j,size,grid_size,flag;
string *dyna_room,*room_names,dir1,dir2,dir3,dir4,rev_dir1,rev_dir2,rev_dir3,rev_dir4,*dirs,*rev_dirs,*cur_exits;
object dyna_npc,*room_object,*old_npc,cur_room;
mixed *room_list,*npc_list,*temp_list;
int int_dir;

int regenerate_map()
{
        int kk;

        room_list = get_dir(DOOM_PATH+"/dynamic/*.c");  
        for(kk=0;kk<sizeof(room_list);kk++)
                room_list[kk] = DOOM_PATH+"/dynamic/"+room_list[kk];
        room_list += additional_room;                               

        dyna_room = ({});
        while(sizeof(room_list))
        {
                j = random(sizeof(room_list));
                dyna_room += ({room_list[j]});
                room_list -= ({room_list[j]});
        }//隨機分配位置完畢                                             

        size = sizeof(dyna_room);

        room_object = ({});
        for(i=0;i<size;i++)
        {
        if( !(cur_room = find_object(dyna_room[i])) )
                cur_room = load_object(dyna_room[i]);
                tell_room(cur_room,HIY"從山莊中心傳來機關發動的隆隆聲...\n頓時一陣天旋地轉...\n");
                delete("exits", cur_room);
                delete("blocks", cur_room);
                set("no_clean_up", 1, cur_room);
                room_object += ({cur_room});
        }

        //開始生成路徑
        for(i=0;i<size;i++)
        {
                //生成四個不同的方向對
                dirs =  ({      "north","northeast","northwest","south",
                                "southwest","southeast","east","west",    
                                "up","down","enter","out",
                                "northup","northdown","eastup","eastdown",
                                "westup","westdown","southup","southdown",
                        });

                rev_dirs = ({   "south","southwest","southeast","north",
                                "northeast","northwest","west","east",
                                "down","up","out","enter",
                                "southdown","southup","westdown","westup",
                                "eastdown","eastup","northdown","northup",
                           });                  

                int_dir = random(sizeof(dirs));
                dir1 = dirs[int_dir];
                rev_dir1 = rev_dirs[int_dir];           
                dirs -= ({dir1});
                rev_dirs -= ({rev_dir1});
                
                int_dir = random(sizeof(dirs));
                dir2 = dirs[int_dir];
                rev_dir2 = rev_dirs[int_dir];           
                dirs -= ({dir2});
                rev_dirs -= ({rev_dir2});

                if(i>0)
                {
                set("exits/"+dir1, dyna_room[i-1], (room_object[i]));
                set("exits/"+rev_dir1, dyna_room[i], (room_object[i-1]));
                }
                int_dir = random(size);                                  
                if( (int_dir != i) && !(query("exits/"+rev_dir2, (room_object[int_dir]))) )
                {
                set("exits/"+dir2, dyna_room[int_dir], (room_object[i]));
                set("exits/"+rev_dir2, dyna_room[i], (room_object[int_dir]));
                }
                int_dir = random(size);
        tell_room(room_object[i],HIW"待聲音停歇下來，你發現一切都已經變了...\n"NOR);
        }                                                   
        set("exits/south", DOOM_PATH+"/yongdao3", (room_object[size-1]));
        set("exits/north", DOOM_PATH+"/hall", (room_object[0]));
        return 1;
}
