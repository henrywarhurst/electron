// Copyright (c) 2013 GitHub, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_API_ATOM_API_MENU_H_
#define ATOM_BROWSER_API_ATOM_API_MENU_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "ui/base/models/simple_menu_model.h"
#include "native_mate/wrappable.h"

namespace atom {

class NativeWindow;

namespace api {

class MenuMac;

class Menu : public mate::Wrappable,
             public ui::SimpleMenuModel::Delegate {
 public:
  static mate::Wrappable* Create();

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Handle<v8::ObjectTemplate> prototype);

#if defined(OS_MACOSX)
  // Set the global menubar.
  static void SetApplicationMenu(Menu* menu);

  // Fake sending an action from the application menu.
  static void SendActionToFirstResponder(const std::string& action);
#endif

 protected:
  Menu();
  virtual ~Menu();

  // ui::SimpleMenuModel::Delegate implementations:
  virtual bool IsCommandIdChecked(int command_id) const OVERRIDE;
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;
  virtual bool IsCommandIdVisible(int command_id) const OVERRIDE;
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;
  virtual bool IsItemForCommandIdDynamic(int command_id) const OVERRIDE;
  virtual string16 GetLabelForCommandId(int command_id) const OVERRIDE;
  virtual string16 GetSublabelForCommandId(int command_id) const OVERRIDE;
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;

  virtual void Popup(NativeWindow* window) = 0;

  scoped_ptr<ui::SimpleMenuModel> model_;

 private:
  void InsertItemAt(int index, int command_id, const base::string16& label);
  void InsertSeparatorAt(int index);
  void InsertCheckItemAt(int index,
                         int command_id,
                         const base::string16& label);
  void InsertRadioItemAt(int index,
                         int command_id,
                         const base::string16& label,
                         int group_id);
  void InsertSubMenuAt(int index,
                       int command_id,
                       const base::string16& label,
                       Menu* menu);
  void SetSublabel(int index, const base::string16& sublabel);
  void Clear();
  int GetIndexOfCommandId(int command_id);
  int GetItemCount() const;
  int GetCommandIdAt(int index) const;
  base::string16 GetLabelAt(int index) const;
  base::string16 GetSublabelAt(int index) const;
  bool IsItemCheckedAt(int index) const;
  bool IsEnabledAt(int index) const;
  bool IsVisibleAt(int index) const;

#if defined(OS_WIN) || defined(TOOLKIT_GTK)
  void AttachToWindow(NativeWindow* window);
#endif

  DISALLOW_COPY_AND_ASSIGN(Menu);
};

}  // namespace api

}  // namespace atom

#endif  // ATOM_BROWSER_API_ATOM_API_MENU_H_
