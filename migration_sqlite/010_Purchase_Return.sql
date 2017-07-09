CREATE TABLE purchaseitemreturns (
    `id` INTEGER PRIMARY KEY,
    `created_at` DATETIME DEFAULT (datetime('now', 'localtime')),
    `updated_at` DATETIME DEFAULT (datetime('now', 'localtime')),
    `deleted_at` DATETIME NULL,
    `barcode` VARCHAR(128) NOT NULL DEFAULT '',
    `count` FLOAT NOT NULL DEFAULT '0',
    `price` DECIMAL(15, 2) NOT NULL DEFAULT 0,
    `suplier_id` INT NOT NULL,
    `purchase_item_id` INT NOT NULL,
    `return_type` TINYINT NOT NULL DEFAULT 0,
    `return_date` DATE NULL,
    `status` TINYINT NOT NULL DEFAULT 0,
    `total` DECIMAL(15, 2) NOT NULL DEFAULT 0,
    `bank_id` INT NOT NULL DEFAULT 0,
    `return_payment` DECIMAL(15, 2) NOT NULL DEFAULT 0,
    `note` VARCHAR(255) NOT NULL DEFAULT ''
);
-- separator
CREATE INDEX PURCHASEITEMRETURN ON sellprices (barcode);