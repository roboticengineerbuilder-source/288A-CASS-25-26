#include "customs/autonselector.hpp"
#include "customs/autons.hpp"
#include "customs/roboports.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "pros/apix.h"
#include "liblvgl/lvgl.h"

namespace selector{

int auton;
int autonCount;
const char *btnmMap[] = {"","","","","","","","","","",""}; // up to 10 autons

lv_obj_t *tabview;
lv_obj_t *redBtnm;
lv_obj_t *blueBtnm;

int getAuton() { return auton; }

void redBtnmAction(lv_event_t *e){
    
    lv_obj_t* btnm = (lv_obj_t*) lv_event_get_target(e); 
    uint32_t id = lv_buttonmatrix_get_selected_button(btnm); 
    const char* txt = lv_buttonmatrix_get_button_text(btnm, id);

	for(int i = 0; i < autonCount; i++){
		if(strcmp(txt, btnmMap[i]) == 0){
			auton = i+1;
		}
	}

	return; // return OK because the button matrix is not deleted
}

void blueBtnmAction(lv_event_t *e){

    lv_obj_t* btnm = (lv_obj_t*) lv_event_get_target(e); 
    uint32_t id = lv_buttonmatrix_get_selected_button(btnm); 
    const char* txt = lv_buttonmatrix_get_button_text(btnm, id);
	//printf("blue button: %s released\n", txt);

	for(int i = 0; i < autonCount; i++){
		if(strcmp(txt, btnmMap[i]) == 0){
			auton = -(i+1);
		}
	}

	return; // return OK because the button matrix is not deleted
}

void skillsBtnAction(lv_event_t *e){
  //printf("skills pressed");
	auton = 0;
	return;
}

int tabWatcher() {
	int activeTab = lv_tabview_get_tab_active(tabview);
	while(1){
		int currentTab = lv_tabview_get_tab_active(tabview);

		if(currentTab != activeTab){
			activeTab = currentTab;
			if(activeTab == 0){
				if(auton == 0) auton = 1;
				auton = abs(auton);
				lv_buttonmatrix_set_selected_button(redBtnm, abs(auton)-1);
			}else if(activeTab == 1){
				if(auton == 0) auton = -1;
				auton = -abs(auton);
				lv_buttonmatrix_set_selected_button(blueBtnm, abs(auton)-1);
			}else{
				auton = 0;
			}
		}

		pros::delay(20);
	}
}

void init(int hue, int default_auton, const char **autons){

	int i = 0;
	do{
	btnmMap[i] = autons[i];
		i++;
	}while(strcmp(autons[i], "") != 0);

	autonCount = i;
	auton = default_auton;

	// lvgl theme
	lv_theme_t *th = lv_theme_default_init(lv_display_get_default(), lv_color_hex(hue), lv_color_hex(hue), false, LV_FONT_DEFAULT ); //Set a HUE value and keep font default RED
	lv_display_set_theme(lv_display_get_default(), th);

	// create a tab view object
	tabview = lv_tabview_create(lv_screen_active());

	// add 3 tabs (the tabs are page (lv_page) and can be scrolled
	lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Red");
	lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Blue");
	lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");

	//set default tab
	if(auton < 0){
		lv_tabview_set_active(tabview, 1, LV_ANIM_OFF);
	}else if(auton == 0){
		lv_tabview_set_active(tabview, 2, LV_ANIM_OFF);
	}

	// red tab
	redBtnm = lv_buttonmatrix_create(redTab);
	lv_buttonmatrix_set_map(redBtnm, btnmMap);
	lv_obj_add_event_cb(redBtnm, redBtnmAction, LV_EVENT_VALUE_CHANGED, NULL);
	lv_buttonmatrix_set_selected_button(redBtnm, abs(auton)-1);
	lv_obj_set_size(redBtnm, 450, 50);
	lv_obj_set_pos(redBtnm, 0, 100);
	lv_obj_align(redBtnm, LV_ALIGN_CENTER, 0, 0);

	// blue tab
	blueBtnm = lv_buttonmatrix_create(blueTab);
	lv_buttonmatrix_set_map(blueBtnm, btnmMap);
    lv_obj_add_event_cb(blueBtnm, blueBtnmAction, LV_EVENT_VALUE_CHANGED, NULL);
	lv_buttonmatrix_set_selected_button(blueBtnm, abs(auton)-1);
	lv_obj_set_size(blueBtnm, 450, 50);
	lv_obj_set_pos(blueBtnm, 0, 100);
	lv_obj_align(blueBtnm, LV_ALIGN_CENTER, 0, 0);

	// skills tab
	lv_obj_t *skillsBtn = lv_button_create(skillsTab);
	lv_obj_t *label = lv_label_create(skillsBtn);
	lv_label_set_text(label, "Skills");
	lv_obj_add_event_cb(skillsBtn, skillsBtnAction, LV_EVENT_CLICKED, NULL);

	// lv_btn_set_state(skillsBtn, LV_BTN_STATE_TGL_REL);
	lv_obj_set_size(skillsBtn, 450, 50);
	lv_obj_set_pos(skillsBtn, 0, 100);
	lv_obj_align(skillsBtn, LV_ALIGN_CENTER, 0, 0);

	// start tab watcher
	pros::Task tabWatcher_task(tabWatcher);

}

} // namespace selector