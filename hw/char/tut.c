/* tutorial
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include "hw/hw.h"
#include "hw/pci/pci.h"
#include "qemu/event_notifier.h"
#include "qemu/osdep.h"

typedef struct PCITutDevState {
    PCIDevice parent_obj;
} PCITutDevState;

#define TYPE_PCI_TUT_DEV "pci-tutdev"

#define PCI_TUT_DEV(obj) \
    OBJECT_CHECK(PCITutDevState, (obj), TYPE_PCI_TUT_DEV)

static int pci_tutdev_init(PCIDevice *pci_dev)
{
    PCITutDevState *d = PCI_TUT_DEV(pci_dev);
    uint8_t *pci_conf;
  
    pci_conf = pci_dev->config;
    pci_conf[PCI_INTERRUPT_PIN] = 0; /* no interrupt pin */

    printf("tutorial: loaded\n");
    return 0;
}

static void
pci_tutdev_uninit(PCIDevice *dev)
{
    printf("tutorial: unloaded\n");
}

static void qdev_pci_tutdev_reset(DeviceState *dev)
{
}

static void pci_tutdev_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);

    k->init = pci_tutdev_init;
    k->exit = pci_tutdev_uninit;
    k->vendor_id = 0x1337;
    k->device_id = 0x0001;
    k->revision = 0x00;
    k->class_id = PCI_CLASS_OTHERS;
    dc->desc = "PCI tutorial";
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
    dc->reset = qdev_pci_tutdev_reset;
}

static const TypeInfo pci_tut_info = {
    .name          = TYPE_PCI_TUT_DEV,
    .parent        = TYPE_PCI_DEVICE,
    .instance_size = sizeof(PCITutDevState),
    .class_init    = pci_tutdev_class_init,
};

static void pci_tut_register_types(void)
{
    type_register_static(&pci_tut_info);
}

type_init(pci_tut_register_types)

