#include <linux/module.h>
#include <linux/virtio.h>
#include <linux/virtio_config.h>

#define VIRTIO_TAG_OFFSET 0
#define VIRTIO_TAG_DEVICE_ID 40

static uint64_t tag_value;

struct virtio_tag_config {
    uint64_t tag;
};


/* Probe function to read the tag from Virtio config space */
static int virtio_tag_probe(struct virtio_device *dev) {
    /* Read 8-byte tag from the Virtio config space */
    virtio_cread_le(dev, struct virtio_tag_config, tag, &tag_value);
    pr_info("Virtio-Tag: Found device with tag: 0x%llx\n", tag_value);
    return 0;
}

/* Remove function */
static void virtio_tag_remove(struct virtio_device *dev) {
    pr_info("Virtio-Tag: Device removed\n");
}

/* Virtio Device ID Table */
static struct virtio_device_id virtio_tag_id_table[] = {
    { VIRTIO_TAG_DEVICE_ID, VIRTIO_DEV_ANY_ID },
    { 0 }
};

/* Virtio Driver */
static struct virtio_driver virtio_tag_driver = {
    .driver.name = "virtio_tag",
    .id_table = virtio_tag_id_table,
    .probe = virtio_tag_probe,
    .remove = virtio_tag_remove,
};

module_virtio_driver(virtio_tag_driver);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Built-in Virtio-Tag Driver");
